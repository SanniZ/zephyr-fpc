/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
	 
#include <zephyr.h>
#include <sys/printk.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "fpc_log.h"
#include "fpc_ta_router.h"
#include "fpc_types.h"

#include "app_ipc.h"


static void dispatch_event(const uevent_t* ev) {
    if (ev == NULL)
        return;

    if (ev->event == 0) {
        /* not really an event, do nothing */
        LOGE("got an empty event\n");
        return;
    }

    /* check if we have handler */
    tipc_event_handler_t* handler = (tipc_event_handler_t*)(ev->cookie);
    if (handler && handler->proc) {
        /* invoke it */
        handler->proc(ev, handler->priv);
        return;
    }

    /* no handler? close it */
    LOGE("no handler for event (0x%x) with handle %d\n", ev->event, ev->handle);

    //close(ev->handle);

}


int main(void) {
    long rc;
    uevent_t event;

    fpc_fingerprint_srv_ctx_t ctx;
    rc = fpc_fingerprint_ipc_init(&ctx);
    if (rc < 0) {
        LOGE("failed (%ld) to initialize fpc_fingerprint", rc);
        return rc;
    }

    /* enter main event loop */
    while (true) {
        event.handle = 0;
        event.event = 0;
        event.cookie = NULL;

        rc = wait_any(&event, -1);
        if (rc < 0) {
            LOGE("wait_any failed (%ld)", rc);
            break;
        }

        if (rc == 0) { /* got an event */
            rc = fpc_ta_router_init();
            if (rc) {
                LOGE("%s ta route init failed %ld\n", __func__, rc);
                return -1;
            }
            dispatch_event(&event);
        }
    }

    fpc_ta_router_exit();

    return 0;

}
