#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408D40..0x00408D51: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408d40() {
    __asm {
    L_00408d40:
        test esi,esi
    L_00408d42:
        je short L_00408d51
    L_00408d44:
        push esi
    L_00408d45:
        call asm_FUN_00408af0_00408af0
    L_00408d4a:
        push esi
    L_00408d4b:
        call asm_free_004524a1
    L_00408d50:
        pop ecx
    L_00408d51:
        ret
    }
}
