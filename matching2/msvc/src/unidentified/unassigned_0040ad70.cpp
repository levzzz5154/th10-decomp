#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD70..0x0040AD77: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ad70() {
    __asm {
    L_0040ad70:
        push 1
    L_0040ad72:
        call asm_MenuCursor_Advance_0044bea0
    L_0040ad77:
        ret
    }
}
