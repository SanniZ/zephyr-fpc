#ifndef __HECI_BRIDGE_H__
#define __HECI_BRIDGE_H__

#include "heci.h"



typedef signed long int ssize_t;

size_t heci_host_put(void *buf, size_t size);
size_t heci_host_get(void *buf, size_t size);
int heci_host_send_flow_control(uint32_t conn_id);
size_t heci_client_put(void *buf, size_t size);
size_t heci_client_get(void *buf, size_t size);
int heci_client_register(heci_client_t *client);

#endif
