#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046586B..0x00465874: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046586b() {
    __asm {
    L_0046586b:
        mov eax,471854h
    L_00465870:
        jmp asm_CxxFrameHandler_0046276d
    }
}
