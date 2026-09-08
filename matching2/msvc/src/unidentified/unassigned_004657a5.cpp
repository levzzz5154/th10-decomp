#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657A5..0x004657AE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004657a5() {
    __asm {
    L_004657a5:
        mov eax,471774h
    L_004657aa:
        jmp asm_CxxFrameHandler_0046276d
    }
}
