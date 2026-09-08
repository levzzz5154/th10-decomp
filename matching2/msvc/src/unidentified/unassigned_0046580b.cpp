#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046580B..0x00465814: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046580b() {
    __asm {
    L_0046580b:
        mov eax,4717E8h
    L_00465810:
        jmp asm_CxxFrameHandler_0046276d
    }
}
