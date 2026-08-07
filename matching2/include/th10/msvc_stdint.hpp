#pragma once

#ifdef _MSC_VER
#include <stddef.h>
#endif

// Minimal fixed-width integer aliases for the MSVC 7.1 overlay build, which
// predates <cstdint>. The host-side (non-MSVC) build keeps using <cstdint>.

typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef signed short       int16_t;
typedef unsigned short     uint16_t;
typedef signed int         int32_t;
typedef unsigned int       uint32_t;
typedef signed long long   int64_t;
typedef unsigned long long uint64_t;

typedef int32_t            intptr_t;
typedef uint32_t           uintptr_t;

#ifdef _MSC_VER
namespace std {
typedef ::int8_t int8_t;
typedef ::uint8_t uint8_t;
typedef ::int16_t int16_t;
typedef ::uint16_t uint16_t;
typedef ::int32_t int32_t;
typedef ::uint32_t uint32_t;
typedef ::int64_t int64_t;
typedef ::uint64_t uint64_t;
}
#endif
