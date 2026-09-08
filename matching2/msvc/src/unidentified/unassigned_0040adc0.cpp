#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ADC0..0x0040ADC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040adc0() {
    __asm {
    L_0040adc0:
        ret
    }
}
