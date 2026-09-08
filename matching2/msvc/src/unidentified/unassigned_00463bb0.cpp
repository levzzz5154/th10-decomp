#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463BB0..0x00463BB9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463bb0() {
    __asm {
    L_00463bb0:
        mov edx,477010h
    L_00463bb5:
        jmp asm_ctrandisp2_00463d3b
    }
}
