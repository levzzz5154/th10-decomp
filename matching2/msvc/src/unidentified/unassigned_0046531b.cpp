#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046531B..0x00465324: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046531b() {
    __asm {
    L_0046531b:
        mov eax,471374h
    L_00465320:
        jmp asm_CxxFrameHandler_0046276d
    }
}
