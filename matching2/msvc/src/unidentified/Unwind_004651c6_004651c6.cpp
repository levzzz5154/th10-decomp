#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651C6..0x004651CD: Unwind@004651c6
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004651c6_004651c6() {
    __asm {
    L_004651c6:
        lea ecx,[ebp-28h]
    L_004651c9:
        jmp asm_LegacyString_Clear_004381f0
    }
}
