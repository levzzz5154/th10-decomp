#pragma once

// MSVC 7.1 predates <stdint.h>; keep the same fixed-width types available to
// the matching compiler and to C++98 host-side contract tests.
#ifdef _MSC_VER
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef signed char         int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;
#else
#include <stdint.h>
#endif
