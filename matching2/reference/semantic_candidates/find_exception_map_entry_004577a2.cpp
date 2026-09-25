#include <stdint.h>

struct ExceptionMapEntry_004577a2 {
    uint32_t exception_code;
    uint32_t signal_number;
    uint32_t action;
};

extern "C" uint32_t data_00473654; // exception-map entry count

// Retail 0x004577A2..0x004577CD receives entries in EDX and code in ESI.
extern "C" ExceptionMapEntry_004577a2* __cdecl
FindExceptionMapEntry_004577a2(
    ExceptionMapEntry_004577a2* entries, uint32_t exception_code) {
    for (uint32_t i = 0; i < data_00473654; ++i) {
        if (entries[i].exception_code == exception_code)
            return &entries[i];
    }
    return 0;
}
