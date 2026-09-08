#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FE7E..0x0045FE86: FUN_0045fe7e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045fe7e_0045fe7e() {
    __asm {
    L_0045fe7e:
        call asm_getptd_00456357
    L_0045fe83:
        add eax,58h
    L_0045fe86:
        ret
    }
}
