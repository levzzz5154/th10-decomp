#include "asm_symbols.hpp"

// Frees the owned strings in an LC_TIME record. The order follows the retail
// routine because each call can affect the process heap state.
extern "C" void __cdecl asm_free_lc_time_0045b39a(void* time_info) {
    if (time_info == 0) {
        return;
    }

    void** const entries = static_cast<void**>(time_info);
    for (unsigned int index = 1; index <= 6; ++index) {
        asm_free_00452422(entries[index]);
    }
    asm_free_00452422(entries[0]);
    for (unsigned int index = 8; index <= 13; ++index) {
        asm_free_00452422(entries[index]);
    }
    asm_free_00452422(entries[7]);
    for (unsigned int index = 14; index <= 42; ++index) {
        asm_free_00452422(entries[index]);
    }
}
