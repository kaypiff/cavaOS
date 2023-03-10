
#pragma once

#include <stdarg.h>
#include <types.hh>

namespace cava {
    int putchar(int c);
    int printf(const char *__restrict, ...);
    int puts(const char *str);
    int vaprintf(const char *__restrict, va_list args);
    void clear();
    void scroll();
}
