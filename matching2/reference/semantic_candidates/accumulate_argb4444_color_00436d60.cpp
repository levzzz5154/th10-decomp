#include <stdint.h>

struct ColorTotals_00436d60 {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
};

// Retail 0x00436D60..0x00436D96 uses EAX for RGB totals, EDX for an
// ARGB4444 pixel, and ESI for the count of qualifying pixels.
extern "C" void __cdecl AccumulateArgb4444Color_00436d60(
    ColorTotals_00436d60* totals, const uint16_t* packed_word,
    uint32_t* qualifying_count) {
    const uint16_t packed = *packed_word;
    if ((packed & 0xF000u) == 0)
        return;

    totals->red += (packed >> 8) & 0xFu;
    totals->green += (packed >> 4) & 0xFu;
    totals->blue += packed & 0xFu;
    ++*qualifying_count;
}
