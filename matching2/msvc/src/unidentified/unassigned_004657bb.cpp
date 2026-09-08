#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657BB..0x004657C4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004657bb() {
    __asm {
    L_004657bb:
        mov eax,471798h
    L_004657c0:
        jmp asm_CxxFrameHandler_0046276d
    }
}
