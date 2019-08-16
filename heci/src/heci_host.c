
#define LOG_TAG "heci_host"

#include <zephyr.h>
#include <string.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_mem.h"
#include "fpc_tac.h"

#include "heci_bridge.h"

ssize_t heci_host_write(void *buf, size_t size) {
    return heci_host_put(buf, size);
}

ssize_t heci_host_read(void *buf, size_t size) {
    return heci_host_get(buf, size);
}

int heci_host_call(void *in, uint32_t in_size, void *out,
                           uint32_t *out_size) {
    ssize_t rc = heci_host_write(in, in_size);

    if (rc < 0) {
        LOGE("%s failed to send\n", __func__);
        return -FPC_ERROR_COMM;
    }

    rc = heci_host_read(out, *out_size);
    if (rc < 0) {
        LOGE("%s failed to retrieve", __func__);
        return -FPC_ERROR_COMM;
    }

    if ((size_t) rc < in_size) {
        LOGE("invalid response size (%d)\n", (int) rc);
        return -FPC_ERROR_COMM;
    }

    return 0;
}
