#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465370..0x00465379: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465370() {
    __asm {
    L_00465370:
        mov eax,471448h
    L_00465375:
        jmp asm_CxxFrameHandler_0046276d
    }
}
