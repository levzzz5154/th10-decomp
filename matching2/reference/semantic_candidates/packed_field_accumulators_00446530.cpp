#include <stdint.h>

struct ColorTotals_00446530 {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
};

// Retail 0x00446530..0x00446566 accepts an ARGB1555 pixel when alpha is set.
extern "C" void __cdecl AccumulateArgb1555Color_00446530(
    ColorTotals_00446530* totals, const uint16_t* packed_word,
    uint32_t* qualifying_count) {
    const uint16_t packed = *packed_word;
    if ((packed & 0x8000u) == 0)
        return;

    totals->red += (packed >> 10) & 0x1Fu;
    totals->green += (packed >> 5) & 0x1Fu;
    totals->blue += packed & 0x1Fu;
    ++*qualifying_count;
}

// Retail 0x00446570..0x004465A6 accepts ARGB4444 with nonzero alpha.
extern "C" void __cdecl AccumulateArgb4444Color_00446570(
    ColorTotals_00446530* totals, const uint16_t* packed_word,
    uint32_t* qualifying_count) {
    const uint16_t packed = *packed_word;
    if ((packed & 0xF000u) == 0)
        return;

    totals->red += (packed >> 8) & 0xFu;
    totals->green += (packed >> 4) & 0xFu;
    totals->blue += packed & 0xFu;
    ++*qualifying_count;
}
