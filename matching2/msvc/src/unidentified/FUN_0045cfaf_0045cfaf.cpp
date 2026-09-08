#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CFAF..0x0045CFB7: FUN_0045cfaf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045cfaf_0045cfaf() {
    __asm {
    L_0045cfaf:
        push 0Dh
    L_0045cfb1:
        call asm_FUN_00453b3f_00453b3f
    L_0045cfb6:
        pop ecx
    L_0045cfb7:
        ret
    }
}
