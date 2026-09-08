#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455ADE..0x00455B0F: ___updatetlocinfo
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_updatetlocinfo_00455ade() {
    __asm {
    L_00455ade:
        push 0Ch
    L_00455ae0:
        push 46A9F0h
    L_00455ae5:
        call asm_SEH_prolog_00454bbc
    L_00455aea:
        push 0Ch
    L_00455aec:
        call asm_lock_00453c0c
    L_00455af1:
        pop ecx
    L_00455af2:
        and dword ptr [ebp-4],0
    L_00455af6:
        call asm_updatetlocinfo_lk_004558cc
    L_00455afb:
        mov dword ptr [ebp-1Ch],eax
    L_00455afe:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00455b02:
        call asm_FUN_00455b10_00455b10
    L_00455b07:
        mov eax,dword ptr [ebp-1Ch]
    L_00455b0a:
        call asm_SEH_epilog_00454bf7
    L_00455b0f:
        ret
    }
}
