#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464F15..0x00464F2B: FUN_00464f15
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464f15_00464f15() {
    __asm {
    L_00464f15:
        mov edx,dword ptr [esp+4]
    L_00464f19:
        and edx,300h
    L_00464f1f:
        or edx,7Fh
    L_00464f22:
        mov word ptr [esp+6],dx
    L_00464f27:
        fldcw word ptr [esp+6]
    L_00464f2b:
        ret
    }
}
