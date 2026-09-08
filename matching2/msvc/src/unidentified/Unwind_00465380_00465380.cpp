#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465380..0x00465387: Unwind@00465380
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465380_00465380() {
    __asm {
    L_00465380:
        lea ecx,[ebp-18h]
    L_00465383:
        jmp asm_1FileHandle_00435340
    }
}
