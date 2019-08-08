
#include "zephyr.h"

#include <string.h>


void fpc_memset(void *s,int ch,size_t n) {
     memset(s, ch, n);
}

void* fpc_memcpy(void* destination, const void* source, size_t num ) {
    return memcpy(destination, source, num);
}

void* fpc_malloc(size_t size) {
    return k_malloc(size);
}

void fpc_free(void* mem) {
    k_free(mem);
}

void* fpc_calloc(size_t nmemb, size_t size) {
    return k_calloc(nmemb, size);
}
