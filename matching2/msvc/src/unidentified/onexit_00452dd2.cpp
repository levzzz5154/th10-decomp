#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452DD2..0x00452E03: __onexit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_onexit_00452dd2() {
    __asm {
    L_00452dd2:
        push 0Ch
    L_00452dd4:
        push 46A6E0h
    L_00452dd9:
        call asm_SEH_prolog_00454bbc
    L_00452dde:
        call asm_FUN_00457577_00457577
    L_00452de3:
        and dword ptr [ebp-4],0
    L_00452de7:
        mov edi,dword ptr [ebp+8]
    L_00452dea:
        call asm_onexit_lk_00452d2a
    L_00452def:
        mov dword ptr [ebp-1Ch],eax
    L_00452df2:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00452df6:
        call asm_FUN_00452e04_00452e04
    L_00452dfb:
        mov eax,dword ptr [ebp-1Ch]
    L_00452dfe:
        call asm_SEH_epilog_00454bf7
    L_00452e03:
        ret
    }
}
