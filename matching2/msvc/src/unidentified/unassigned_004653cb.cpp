#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004653CB..0x004653D4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004653cb() {
    __asm {
    L_004653cb:
        mov eax,4714B4h
    L_004653d0:
        jmp asm_CxxFrameHandler_0046276d
    }
}
