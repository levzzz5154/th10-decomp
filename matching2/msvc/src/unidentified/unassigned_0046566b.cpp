#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046566B..0x00465674: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046566b() {
    __asm {
    L_0046566b:
        mov eax,4716C0h
    L_00465670:
        jmp asm_CxxFrameHandler_0046276d
    }
}
