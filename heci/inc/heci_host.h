

#ifndef __HECI_HOST_H__
#define __HECI_HOST_H__

#include <zephyr.h>

#include "fpc_tac.h"

int heci_host_read(void *buf, size_t size);
int heci_host_write(void *buf, size_t size);
int heci_host_call(void *in, uint32_t in_size, void *out,
                           uint32_t *out_size);

#endif /* _HECI_H_ */
