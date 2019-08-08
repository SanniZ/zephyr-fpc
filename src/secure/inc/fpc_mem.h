/*
 * Copyright (c) 2015 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */
#ifndef _FPC_MEM_H_DEFINED_
#define _FPC_MEM_H_DEFINED_
#include <stdlib.h>

void fpc_get_timestamp(uint64_t* time);
void fpc_memset(void *s,int ch,size_t n);
void* fpc_memcpy(void* destination, const void* source, size_t num );
void* fpc_malloc(size_t size);
void* fpc_calloc(size_t nmemb, size_t size);
void fpc_free(void* mem);
void fpc_free(void* mem);
#endif
