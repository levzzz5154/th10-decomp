#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AFB0..0x0041AFC1: FUN_0041afb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041afb0_0041afb0() {
    __asm {
    L_0041afb0:
        test esi,esi
    L_0041afb2:
        je short L_0041afc1
    L_0041afb4:
        push esi
    L_0041afb5:
        call asm_FUN_0041adf0_0041adf0
    L_0041afba:
        push esi
    L_0041afbb:
        call asm_free_004524a1
    L_0041afc0:
        pop ecx
    L_0041afc1:
        ret
    }
}
