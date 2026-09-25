#include <stdint.h>

// Retail 0x00454EB8..0x00454EC0 receives the cursor address in EAX.
extern "C" uint32_t __cdecl ReadCursorU32_00454eb8(const uint8_t** cursor) {
    *cursor += 4;
    return *reinterpret_cast<const uint32_t*>(*cursor - 4);
}

// Retail 0x00454EC1..0x00454ECC returns the two words in EDX:EAX.
extern "C" uint64_t __cdecl ReadCursorU64_00454ec1(const uint8_t** cursor) {
    *cursor += 8;
    return *reinterpret_cast<const uint64_t*>(*cursor - 8);
}

// Retail 0x00454ECD..0x00454ED6 changes only AX after loading the cursor
// pointer into EAX. Callers should consume the returned 16-bit value.
extern "C" uint16_t __cdecl ReadCursorU16_00454ecd(const uint8_t** cursor) {
    *cursor += 4;
    return *reinterpret_cast<const uint16_t*>(*cursor - 4);
}
