#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046560F..0x00465618: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046560f() {
    __asm {
    L_0046560f:
        mov eax,471654h
    L_00465614:
        jmp asm_CxxFrameHandler_0046276d
    }
}
