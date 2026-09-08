#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465514..0x0046551D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465514() {
    __asm {
    L_00465514:
        mov eax,471590h
    L_00465519:
        jmp asm_CxxFrameHandler_0046276d
    }
}
