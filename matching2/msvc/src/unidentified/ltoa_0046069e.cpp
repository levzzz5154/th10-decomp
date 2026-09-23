#include "asm_symbols.hpp"

// 0x0046069E..0x004606C4: __ltoa
// Both CRT entry points use 32-bit values on this x86 target.
extern "C" char* __cdecl asm_ltoa_0046069e(long value, char* destination, int radix) {
    return asm_itoa_00460674(static_cast<int>(value), destination, radix);
}
