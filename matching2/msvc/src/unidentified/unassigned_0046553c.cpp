#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046553C..0x00465545: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046553c() {
    __asm {
    L_0046553c:
        mov eax,4715B4h
    L_00465541:
        jmp asm_CxxFrameHandler_0046276d
    }
}
