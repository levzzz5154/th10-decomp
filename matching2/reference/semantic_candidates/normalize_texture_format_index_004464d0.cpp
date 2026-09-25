#include <stdint.h>

extern "C" uint8_t data_00491d78;     // rendering options
extern "C" uint32_t data_0046f288[]; // texture format lookup table

// Retail 0x004464D0..0x004464F9 receives the format index in EAX.
extern "C" uint32_t __cdecl NormalizeTextureFormatIndex_004464d0(
    uint32_t format_index) {
    if ((data_00491d78 & 1u) == 0)
        return format_index;

    const uint32_t format = data_0046f288[format_index];
    if (format == 0x15 || format == 0)
        return 5;
    if (format == 0x14)
        return 3;
    return format_index;
}
