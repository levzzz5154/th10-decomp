#include <stdint.h>

extern "C" void* data_00477810;        // active scene
extern "C" uint32_t data_00474e30;     // input state

// Retail 0x00429A30..0x00429A69 receives the state pointer in EAX.
extern "C" int __cdecl SelectPeriodicActionCode_00429a30(
    const uint8_t* state) {
    const int32_t state_kind =
        *reinterpret_cast<const int32_t*>(state + 0x10);
    if (data_00477810 == 0 || state_kind != 1 ||
        (data_00474e30 & 0x100u) == 0)
        return 1;

    const uint32_t counter =
        *reinterpret_cast<const uint32_t*>(state + 0x1C8);
    return (counter & 3u) != 0 ? 6 : 1;
}
