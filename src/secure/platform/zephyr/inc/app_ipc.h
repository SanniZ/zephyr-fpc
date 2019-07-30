#ifndef __APP_IPC_H__
#define __APP_IPC_H__

typedef struct uevent {
	uint32_t	handle;  /* handle this event is related too */
	uint32_t	event;   /* combination of IPC_HANDLE_POLL_XXX flags */
	void		*cookie; /* cookie aasociated with handle */
} uevent_t;

typedef struct uuid
{
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t time_hi_and_version;
	uint8_t clock_seq_and_node[8];
} uuid_t;

typedef uint32_t handle_t;

typedef void (*event_handler_proc_t)(const uevent_t* ev, void* ctx);

typedef struct tipc_event_handler_s {
    event_handler_proc_t proc;
    void* priv;
} tipc_event_handler_t;

typedef struct fpc_fingerprint_chan_ctx_s {
    tipc_event_handler_t handler;
    uuid_t uuid;
    handle_t chan;
    int32_t (*dispatch)(struct fpc_fingerprint_chan_ctx_s*, void*, uint32_t);
} fpc_fingerprint_chan_ctx_t;

typedef struct fpc_fingerprint_srv_ctx_s {
    handle_t port_secure;
    handle_t port_non_secure;
} fpc_fingerprint_srv_ctx_t;


long fpc_fingerprint_ipc_init(fpc_fingerprint_srv_ctx_t* ctx);

long wait_any (uevent_t *event, uint32_t timeout_msecs);

#endif
