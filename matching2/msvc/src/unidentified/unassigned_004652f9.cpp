#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652F9..0x00465302: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004652f9() {
    __asm {
    L_004652f9:
        mov eax,471350h
    L_004652fe:
        jmp asm_CxxFrameHandler_0046276d
    }
}
