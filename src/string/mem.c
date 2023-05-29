
#include <stddef.h>

/* These functions MUST BE in global scope, otherwise GCC crashes */

void memcpy(void *dest, void *src, size_t n)
{
    __builtin_memcpy(dest, src, n);
}

void memmove(void *dest, void *src, size_t n)
{
    __builtin_memmove(dest, src, n);
}

void *memset(void *p, int v, size_t n)
{
    return __builtin_memset(p, v, n);
}
