#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004051D0..0x004051D6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004051d0() {
    __asm {
    L_004051d0:
        push eax
    L_004051d1:
        call asm_FUN_0043ee30_0043ee30
    L_004051d6:
        ret
    }
}
