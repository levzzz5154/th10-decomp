#include <stdint.h>

struct IndexedRecord_00412750 {
    int32_t status;
    uint32_t first;
    uint32_t second;
    uint32_t third;
};

// Retail 0x00412750..0x00412787 uses ESI for the base, EDX for the index,
// ECX for status, and three stack words for the payload.
extern "C" void __cdecl SetIndexedRecord_00412750(
    uint8_t* base, int32_t index, int32_t status,
    uint32_t first, uint32_t second, uint32_t third) {
    IndexedRecord_00412750* record =
        reinterpret_cast<IndexedRecord_00412750*>(
            base + 0x2494 + index * 0x10);
    record->status = status;
    if (status < 0)
        return;
    record->first = first;
    record->second = second;
    record->third = third;
}
