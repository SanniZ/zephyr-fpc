
#define LOG_TAG "heci_bridge"

#include <zephyr.h>
#include <string.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_mem.h"

#include "app_main.h"
#include "heci.h"

static heci_client_t heci_client;

static K_SEM_DEFINE(heci_client_rx_sem, 0, 1);
static K_SEM_DEFINE(heci_client_tx_sem, 0, 1);

size_t heci_host_put(void *buf, size_t size) {
    memcpy(heci_client.rx_msg->buffer, buf, size);
    heci_client.rx_msg->length = size;
    heci_client.rx_msg->msg_lock = MSG_LOCKED;
    k_sem_give(&heci_client_rx_sem);
    return size;
}

size_t heci_host_get(void *buf, size_t size) {
    k_sem_take(&heci_client_tx_sem, -1);
    memcpy(buf, heci_client.rx_msg->buffer, size);
    heci_client.rx_msg->length = size;
    return size;
}

int heci_host_send_flow_control(uint32_t conn_id) {
    heci_client.rx_msg->msg_lock = MSG_UNLOCKED;
    return 0;
}

size_t heci_client_put(void *buf, size_t size) {
    memcpy(heci_client.rx_msg->buffer, buf, size);
    heci_client.rx_msg->length = size;
    k_sem_give(&heci_client_tx_sem);
    return size;
}

size_t heci_client_get(void *buf, size_t size) {
    //k_sem_take(&heci_client_tx_sem, -1);
    //memcpy(buf, heci_client.tx_buffer, size);
    //heci_client.tx_size = size;
    return size;
}

int heci_client_register(heci_client_t *client) {
    memcpy((void *)&heci_client, (void *)client, sizeof(heci_client_t));
    return 0;
}


static void heci_client_task(void *p1, void *p2, void *p3) {
    LOG_ENTER();
    while(true) {
        k_sem_take(&heci_client_rx_sem, -1);
        heci_client.event_cb(HECI_EVENT_NEW_MSG);
    }
}

static K_THREAD_STACK_DEFINE(heci_bridge_stack, STACK_MAX_SIZE);
static struct k_thread heci_bridge_thread;

void heci_create_client_task(void) {
    k_thread_create(&heci_bridge_thread, heci_bridge_stack, STACK_MAX_SIZE,
				heci_client_task, NULL, NULL, NULL, K_PRIO_PREEMPT(11), 0, 0);
}

//K_THREAD_DEFINE(heci_c_task, STACK_MAX_SIZE, 
//	          heci_client_task, NULL, NULL, NULL,
//	          K_PRIO_PREEMPT(11), 0, 2000);
