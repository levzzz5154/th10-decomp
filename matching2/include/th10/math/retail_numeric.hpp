#pragma once

#include <cstdint>
#include <cstring>

// Value-level helpers for the executable's 32-bit arithmetic. These do not
// reproduce x87 exception/status flags or change the caller's control word.
inline int Retail_I32Bits(std::uint32_t bits) {
    static_assert(sizeof(int) == sizeof(bits), "retail integers are 32-bit");
    int result;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}

inline int Retail_AddI32(int value, int increment) {
    return Retail_I32Bits(static_cast<std::uint32_t>(value) +
                          static_cast<std::uint32_t>(increment));
}

// __ftol2 (0x00463B2C) returns an int64 in EDX:EAX. These callers consume
// EAX, including modulo-2^32 results outside the signed-int range. Masked
// invalid conversion produces the integer-indefinite value, whose low word
// is zero. Keep the retained argument wide until the integer conversion.
inline int Retail_TruncateI32(long double value) {
    const long double limit = 9223372036854775808.0L;
    if (!(value >= -limit && value < limit))
        return 0;
    return Retail_I32Bits(static_cast<std::uint32_t>(
        static_cast<std::int64_t>(value)));
}
