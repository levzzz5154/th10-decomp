#include <stdint.h>

// Retail 0x0042AC90..0x0042ACAD receives the buffer in ESI and size in EDX.
extern "C" uint32_t __cdecl SumPayloadBytes_0042ac90(
    const uint8_t* buffer, int32_t total_bytes) {
    uint32_t sum = 0;
    for (int32_t i = 8; i < total_bytes; ++i)
        sum += buffer[i];
    return sum;
}
