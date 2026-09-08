#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653A8..0x004653B1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004653a8() {
    __asm {
    L_004653a8:
        mov eax,471490h
    L_004653ad:
        jmp asm_CxxFrameHandler_0046276d
    }
}
