
#define LOG_TAG "fpc_tee_kpi"

#include <zephyr.h>
#include <string.h>

#include "fpc_types.h"
#include "fpc_log.h"
#include "fpc_tac.h"
#include "fpc_ta_targets.h"
#include "fpc_ta_kpi_interface.h"
#include "fpc_tee_internal.h"
#include "fpc_tee.h"


#include "heci.h"
#include "heci_bridge.h"

int fpc_tee_print_build_info(fpc_tee_t* tee)
{
    int status = -1;

    uint32_t size = MAX_BUILDINFO_SIZE + sizeof(fpc_ta_byte_array_msg_t);
    fpc_tac_shared_mem_t* shared_ipc_buffer = fpc_tac_alloc_shared(NULL, size);
    if (!shared_ipc_buffer) {
		LOGE("%s failed to alloc shared memory.\n", __func__);
        goto out;
    }

    fpc_ta_kpi_command_t* command = shared_ipc_buffer->addr;
    command->header.target = TARGET_FPC_TA_KPI;
    command->header.command = FPC_TA_GET_BUILD_INFO_CMD;
    command->build_info.size = MAX_BUILDINFO_SIZE;

    status = fpc_tac_transfer(tee->tac, shared_ipc_buffer);
    if (status) {
        LOGE("%s, fpc_tac_transfer failed %d.", __func__, status);
        goto out;
    }

    status = command->build_info.response;
    if (status) {
        LOGE("%s, get_build_info ta cmd failed %d.", __func__, status);
        goto out;
    }

    char *build_type = strchr((char*)command->build_info.array, '\n');
    if (build_type) {
        *build_type = 0;
        build_type++;
    }

    LOGD("%s : fpcbuildinfo : %s", __func__, command->build_info.array);
    if (build_type) {
        LOGD("%s : fpcbuildtype : %s", __func__, build_type);
    }

out:
    if (shared_ipc_buffer) {
        fpc_tac_free_shared(shared_ipc_buffer);
    }
    return status;
}

