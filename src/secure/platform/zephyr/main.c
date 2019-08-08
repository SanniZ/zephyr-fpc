#include <zephyr.h>
#include <sys/printk.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_ta_router.h"

#include "heci.h"

//#define CONFIG_FP_USES_THREAD_FOR_HECI

#define HECI_CLIENT_FP_GUID	{ 0xa3411200, 0xb4da, 0x4d1c, \
		              { 0xa9, 0x04, 0x20, 0x88, 0x2d, 0xc3, 0xef, 0xea }}

#define RX_MAX_SIZE        4096
#define STACK_MAX_SIZE     1600

static uint32_t conn_id;

static uint8_t rx_buffer[RX_MAX_SIZE];
static uint8_t tx_buffer[RX_MAX_SIZE];

static heci_rx_msg_t rx_msg;
static uint32_t rx_event;

static K_SEM_DEFINE(rx_event_sem, 0, 1);

#ifdef CONFIG_FP_USES_THREAD_FOR_HECI
static K_THREAD_STACK_DEFINE(thread_stack, STACK_MAX_SIZE);
static struct k_thread heci_thread;
static k_tid_t thread_using_heci[] = {&heci_thread};
#endif


/*
  *  send response to host.
  */
static int send_response(uint8_t *buffer, size_t size, int32_t rsp) {
    mrd_t msg = {0};

    msg.buf = buffer;
	msg.len = size;
    return heci_send(conn_id, &msg);
}

/*
  *  process msg and send response.
  */
static void process_msg(uint8_t *buffer, size_t size) {
	void *buf = (void *)tx_buffer;

	fpc_memset(buf, 0, RX_MAX_SIZE);
	fpc_memcpy(buf, (void *)buffer, size);
	send_response(buf, size, fpc_ta_route_command(buf, size));
}

/*
  *  dispatch event.
  */
static void dispatch_event(uint32_t event) {
    switch (event) {
        case HECI_EVENT_NEW_MSG:
            if (rx_msg.msg_lock != MSG_LOCKED) {
                LOGE("%s(): found invalid heci message\n", __func__);
                break;
            }

            if (rx_msg.type == HECI_CONNECT) {
                conn_id = rx_msg.connection_id;
                LOGI("%s(): new conn: %u\n", __func__, conn_id);
            } else if (rx_msg.type == HECI_REQUEST) {
                process_msg(rx_msg.buffer, rx_msg.length);
            }

           /*
	               * send flow control after finishing one message,
	               * allow host to send new request
	               */
            heci_send_flow_control(conn_id);
            break;

        case HECI_EVENT_DISCONN:
            LOGI("%s(): disconnect request conn %d\n", __func__,conn_id);
            heci_complete_disconnect(conn_id);
            break;

        default:
            LOGE("%s(): get wrong heci event %u\n", __func__, event);
            break;
    }
}


/*
  *  waitting for event from heci.
  */
int wait_any(uint32_t *event, uint32_t timeout_msecs) {
    int rc = k_sem_take(&rx_event_sem, timeout_msecs);
    *event = rx_event;
    return rc;
}

/*
  *  loop for events.
  */
static void loop_task(void *p1, void *p2, void *p3) {
	uint32_t event = 0;
    int rc;

    /* enter main event loop */
    while (true) {
		rc = wait_any(&event, K_FOREVER);
        if (rc < 0) {
            LOGE("%s() wait_any failed (%d)\n", __func__, rc);
            break;
        }
		/* run route init. */
		rc = fpc_ta_router_init();
        if (rc) {
            LOGE("%s() route init failed %d\n", __func__, rc);
            break;
        }
		/* dispatch event*/
        dispatch_event(event);
    }

    fpc_ta_router_exit();
}

/*
  *  event callback.
  */
static void rx_event_callback(uint32_t event)
{
	rx_event = event;
	k_sem_give(&rx_event_sem);
}

/*
  *  create heci client and register event callback.
  */
static int heci_client_init(void) {
    int rc;
	heci_client_t heci_client = {
		.protocol_id = HECI_CLIENT_FP_GUID,
		.max_msg_size = RX_MAX_SIZE,
		.protocol_ver = 1,
		.max_n_of_connections = 1,
		.dma_header_length = 0,
		.dma_enabled = 0,
		.rx_buffer_len = RX_MAX_SIZE,
		.event_cb = rx_event_callback,
		/* if not in user space it is not needed*/
#ifdef CONFIG_FP_USES_THREAD_FOR_HECI
		.thread_handle_list = thread_using_heci,
		.num_of_threads = sizeof(thread_using_heci) /
				               sizeof(thread_using_heci[0])
#endif
	};

	heci_client.rx_msg = &rx_msg;
	heci_client.rx_msg->buffer = rx_buffer;

    rc = heci_register(&heci_client);
	if (rc) {
		LOGE("%s() failed to register client %d\n", __func__, rc);
		return rc;
	}

    return 0;
}



int main(void) {
	int rc;

	rc = heci_client_init();
	if (rc) {
        LOGE("%s() failed %d to initialize\n", __func__, rc);
        return rc;
    }

#ifdef CONFIG_FP_USES_THREAD_FOR_HECI
    k_thread_create(&heci_thread, thread_stack, STACK_MAX_SIZE,
					loop_task, NULL, NULL, NULL, K_PRIO_PREEMPT(11), 0, 0);
#else
	loop_task(NULL, NULL, NULL);
#endif

    LOGD("%s() exit!\n", __func__);
    return 0;
}

//SYS_INIT(main, POST_KERNEL, 90);
