/*
 * Copyright (c) 2017 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */

#define LOG_TAG "fpc_tac"


#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include <trusty/tipc.h>
#include <limits.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fpc_tac.h>
#include <fpc_log.h>
#include <fpc_types.h>
#include <fpc_sysfs.h>

#include "heci_host.h"

struct fpc_tac {
    int st_handle;
    int size_of_max_buffer;
    int sysfs_fd;
};

typedef struct {
    fpc_tac_shared_mem_t shared_mem;
    uint32_t size_mem;
} st_data_t;

#define FPC_TAC_SHARED_BUFFER_SIZE 1024 * 4
#define TRUSTY_DEVICE_NAME "/dev/trusty-ipc-dev0"
#define TADEMO_PORT "com.android.trusty.fpcteeapp"

int trusty_cademo_connect(fpc_tac_t *tac)
{
    return 0;
}

void trusty_cademo_disconnect(fpc_tac_t *tac)
{
    return;
}

int trusty_cademo_call(fpc_tac_t *tac, void *in, uint32_t in_size, void *out,
                           uint32_t *out_size)
{
    (void)tac;
    return heci_host_call(in, in_size, out, out_size);
}


int open(const char * pathname, int flags) {
	static int fd = 1;
    return fd++;
}

int close(int fd) {
    return 0;
}

fpc_tac_t* fpc_tac_open()
{
    fpc_tac_t* tac = malloc(sizeof(fpc_tac_t));
    if (!tac) {
        return NULL;
    }

    memset(tac, 0, sizeof(fpc_tac_t));
    tac->sysfs_fd = -1;

    char path[PATH_MAX];

    if (!fpc_sysfs_path_by_attr(FPC_REE_DEVICE_ALIAS_FILE, FPC_REE_DEVICE_NAME, FPC_REE_DEVICE_PATH,
                                path, PATH_MAX)) {
        goto err;
    }

    tac->sysfs_fd = open(path, O_RDONLY);

    if (tac->sysfs_fd == -1) {
        LOGE("%s open %s failed %i", __func__, path, errno);
        goto err;
    }

    tac->size_of_max_buffer = FPC_TAC_SHARED_BUFFER_SIZE;
    return tac;

err:
    if (tac->sysfs_fd != -1) {
        close(tac->sysfs_fd);
    }

    free(tac);
    return NULL;
}

void fpc_tac_release(fpc_tac_t* tac)
{
    if (!tac) {
        return;
    }

    if (tac->sysfs_fd != -1) {
        close(tac->sysfs_fd);
    }

    free(tac);
}


fpc_tac_shared_mem_t* fpc_tac_alloc_shared(fpc_tac_t* tac, uint32_t size)
{
    (void)tac; // Unused parameter
    st_data_t* st_data = malloc(sizeof(st_data_t));
    if (!st_data) {
		LOGE("%s malloc st_data fail.\n", __func__);
        return NULL;
    }
    st_data->shared_mem.addr = NULL;

    //if ((int)size > tac->size_of_max_buffer ) {
    //    LOGE("%s exceed the max buffer (%d) ", __func__, size);
    //    goto err;
    //}

    st_data->size_mem = size;

    st_data->shared_mem.addr = (void*) malloc (st_data->size_mem);
    if (st_data->shared_mem.addr == NULL) {
        LOGE("%s malloc failed with error %i", __func__, -errno);
        goto err;
    }

    return (fpc_tac_shared_mem_t*) st_data;

err:
    fpc_tac_free_shared((fpc_tac_shared_mem_t*) st_data);
    return NULL;
}

void fpc_tac_free_shared(fpc_tac_shared_mem_t* shared_buffer)
{
    if (!shared_buffer) {
        return;
    }

    st_data_t* st_data = (st_data_t*) shared_buffer;

    if (st_data->shared_mem.addr) {
        free(st_data->shared_mem.addr);
    }

    free(shared_buffer);
}

int fpc_tac_transfer(fpc_tac_t* tac, fpc_tac_shared_mem_t *shared_buffer)
{
    int status = 0;

    st_data_t* recv_buf = NULL;
    st_data_t* send_buf = (st_data_t*) shared_buffer;

    if(!send_buf || !send_buf->shared_mem.addr) {
        LOGE("%s empty send_buff \n", __func__);
        return -1;
    }

    recv_buf = (st_data_t*) malloc(sizeof(st_data_t));
    if (!recv_buf) {
        LOGE("%s recv_buf alloc failed \n", __func__);
        status = -2;
        goto out;
    }

    memset(recv_buf, 0, sizeof(st_data_t));
    recv_buf->size_mem = send_buf->size_mem + sizeof(int32_t);
    recv_buf->shared_mem.addr = (void*) malloc( recv_buf->size_mem);
    if (!recv_buf->shared_mem.addr) {
        LOGE("%s recv_buf->sharee_mem alloc failed \n", __func__);
        status = -2;
        goto out;
    }
    memset(recv_buf->shared_mem.addr, 0, recv_buf->size_mem);

    status = trusty_cademo_call(tac, send_buf->shared_mem.addr, send_buf->size_mem,
                                recv_buf->shared_mem.addr, &recv_buf->size_mem);

    memcpy(shared_buffer->addr, recv_buf->shared_mem.addr, send_buf->size_mem);

    int32_t *response = (int32_t*)((uint8_t*)(recv_buf->shared_mem.addr) + send_buf->size_mem);
    if (status || *response) {
        LOGE("%s send_cmd failed %i\n", __func__, status ? status : *response);
        status = -3;
        goto out;
    }
out:
    if (recv_buf) {
        if(recv_buf->shared_mem.addr) {
            free(recv_buf->shared_mem.addr);
        }
        free(recv_buf);
    }
    return status;
}

