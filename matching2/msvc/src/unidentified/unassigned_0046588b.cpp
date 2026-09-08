#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046588B..0x00465894: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046588b() {
    __asm {
    L_0046588b:
        mov eax,471878h
    L_00465890:
        jmp asm_CxxFrameHandler_0046276d
    }
}
