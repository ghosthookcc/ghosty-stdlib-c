#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdarg.h>

#if defined(DEBUG_MODE_ON) && DEBUG_MODE_ON
#define DebugPrint(format, ...) printf(format, ##__VA_ARGS__)
#else 
#define DebugPrint(format, ...)
#endif

#define STATIC_CAST(type, expr)  ((type)(expr))
#define VOIDPTR_CAST(type, expr) (*(type*)(expr))

#endif // COMMON_H