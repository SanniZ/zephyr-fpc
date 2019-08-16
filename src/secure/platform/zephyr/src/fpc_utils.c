/*
 * Copyright (c) 2017 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */

#include <zephyr.h>
#include <stdio.h>
#include <time.h>

#include "fpc_types.h"
#include "fpc_log.h"
//#include "fpc_debug.h"
//#include "trusty_std.h"


void fpc_get_timestamp(uint64_t* times) {
    uint64_t stamp;
#ifndef CONFIG_SYS_CLOCK_EXISTS
    stamp = (uint64_t)z_ms_to_ticks(k_uptime_get());
#else
    stamp = z_tick_get();
#endif
	
    *times = (uint64_t)(stamp / 1000);
}

int fpc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    return vsnprintf(str, size, format, ap);
}

