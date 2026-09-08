#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465388..0x00465391: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465388() {
    __asm {
    L_00465388:
        mov eax,47146Ch
    L_0046538d:
        jmp asm_CxxFrameHandler_0046276d
    }
}
