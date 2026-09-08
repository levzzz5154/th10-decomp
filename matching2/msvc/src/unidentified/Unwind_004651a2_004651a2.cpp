#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651A2..0x004651A9: Unwind@004651a2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004651a2_004651a2() {
    __asm {
    L_004651a2:
        lea ecx,[ebp-28h]
    L_004651a5:
        jmp asm_LegacyString_Clear_004381f0
    }
}
