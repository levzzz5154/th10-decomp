#include "asm_symbols.hpp"

// 0x004606C5..0x004606DE: _ultoa.
// Retail passes value in EAX and destination in ECX to _xtoa_00460636.
// Both functions now have typed cdecl interfaces in the semantic source.
extern "C" char* __cdecl asm_ultoa_004606c5(
    unsigned long value, char* destination, int radix) {
    asm_xtoa_00460636(static_cast<unsigned int>(value), destination,
                      static_cast<unsigned int>(radix), 0);
    return destination;
}
