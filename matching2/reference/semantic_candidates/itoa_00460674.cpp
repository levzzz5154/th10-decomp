#include "asm_symbols.hpp"

// 0x00460674..0x0046069D: __itoa
// Retail sends value and destination to xtoa through EAX and ECX.
// Both functions now have typed cdecl interfaces in the semantic source.
extern "C" char* __cdecl asm_itoa_00460674(int value, char* destination, int radix) {
    asm_xtoa_00460636(static_cast<unsigned int>(value), destination,
                      static_cast<unsigned int>(radix),
                      radix == 10 && value < 0);
    return destination;
}
