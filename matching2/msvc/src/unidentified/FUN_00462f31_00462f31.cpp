#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462F31..0x00462F4B: FUN_00462f31
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462f31_00462f31() {
    __asm {
    L_00462f31:
        call asm_getptd_00456357
    L_00462f36:
        cmp dword ptr [eax+84h],0
    L_00462f3d:
        jle short L_00462f4b
    L_00462f3f:
        call asm_getptd_00456357
    L_00462f44:
        add eax,84h
    L_00462f49:
        dec dword ptr [eax]
    L_00462f4b:
        ret
    }
}
