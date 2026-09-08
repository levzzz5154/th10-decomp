#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413690..0x00413699: FUN_00413690
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413690_00413690() {
    __asm {
    L_00413690:
        push edi
    L_00413691:
        mov edi,ecx
    L_00413693:
        call asm_FUN_004135d0_004135d0
    L_00413698:
        pop edi
    L_00413699:
        ret
    }
}
