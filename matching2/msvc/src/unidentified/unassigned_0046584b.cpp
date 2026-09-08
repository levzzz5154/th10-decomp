#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046584B..0x00465854: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046584b() {
    __asm {
    L_0046584b:
        mov eax,471830h
    L_00465850:
        jmp asm_CxxFrameHandler_0046276d
    }
}
