#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465268..0x00465271: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465268() {
    __asm {
    L_00465268:
        mov eax,4712D4h
    L_0046526d:
        jmp asm_CxxFrameHandler_0046276d
    }
}
