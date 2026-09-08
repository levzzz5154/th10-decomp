#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046533B..0x00465345: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046533b() {
    __asm {
    L_0046533b:
        mov eax,471398h
    L_00465340:
        jmp asm_CxxFrameHandler_0046276d
    L_00465345:
        int 3
    }
}
