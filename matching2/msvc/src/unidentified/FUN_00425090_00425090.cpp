#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425090..0x004250A1: FUN_00425090
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00425090_00425090() {
    __asm {
    L_00425090:
        test esi,esi
    L_00425092:
        je short L_004250a1
    L_00425094:
        push esi
    L_00425095:
        call asm_FUN_00424ed0_00424ed0
    L_0042509a:
        push esi
    L_0042509b:
        call asm_free_004524a1
    L_004250a0:
        pop ecx
    L_004250a1:
        ret
    }
}
