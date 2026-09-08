#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653A0..0x004653A7: Unwind@004653a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004653a0_004653a0() {
    __asm {
    L_004653a0:
        lea ecx,[ebp-18h]
    L_004653a3:
        jmp asm_1FileHandle_00435340
    }
}
