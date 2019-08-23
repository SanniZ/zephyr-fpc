#ifndef __FPC_SERVICE_H__
#define __FPC_SERVICE_H__


#define HECI_CLIENT_FP_GUID	{ 0xa3411200, 0xb4da, 0x4d1c, \
		              { 0xa9, 0x04, 0x20, 0x88, 0x2d, 0xc3, 0xef, 0xea }}

#define RX_MAX_SIZE        4096
#define STACK_MAX_SIZE     (20 * 4096)

int fpc_service_start(struct device *unused);

#endif
