#include <stdint.h>

// Retail 0x0044A130..0x0044A154 receives index in AX, table in ECX,
// output flags in EDX, and the selected bit in SI.
extern "C" uint16_t __cdecl ReadSignedByteFlag_0044a130(
    int16_t index, const int8_t* table, uint16_t* output_flags,
    uint16_t selected_bit) {
    if (index < 0)
        return 0;

    const volatile int8_t* entry = table + index;
    *output_flags |= *entry < 0 ? selected_bit : 0;
    // Retail rereads the entry after updating flags, which matters on overlap.
    return *entry < 0 ? selected_bit : 0;
}

// Retail 0x0044A160..0x0044A18A receives index in CX, output flags in
// EDX, the selected bit in SI, and the source mask on the stack.
extern "C" uint16_t __cdecl ReadBitMaskFlag_0044a160(
    int16_t index, uint16_t* output_flags, uint16_t selected_bit,
    uint32_t source_mask) {
    if (index < 0)
        return 0;

    const uint32_t test_bit = 1u << (static_cast<unsigned int>(index) & 31u);
    const bool active = (source_mask & test_bit) != 0;
    *output_flags |= active ? selected_bit : 0;
    return active ? selected_bit : 0;
}
