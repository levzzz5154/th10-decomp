#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD60..0x0040AD67: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ad60() {
    __asm {
    L_0040ad60:
        push 0FFFFFFFFh
    L_0040ad62:
        call asm_MenuCursor_Advance_0044bea0
    L_0040ad67:
        ret
    }
}
