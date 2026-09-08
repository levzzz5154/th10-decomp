#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457250..0x00457284: __isindst
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isindst_00457250() {
    __asm {
    L_00457250:
        push 0Ch
    L_00457252:
        push 46AAE0h
    L_00457257:
        call asm_SEH_prolog_00454bbc
    L_0045725c:
        push 6
    L_0045725e:
        call asm_lock_00453c0c
    L_00457263:
        pop ecx
    L_00457264:
        and dword ptr [ebp-4],0
    L_00457268:
        mov ebx,dword ptr [ebp+8]
    L_0045726b:
        call asm_isindst_lk_00457048
    L_00457270:
        mov dword ptr [ebp-1Ch],eax
    L_00457273:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00457277:
        call asm_FUN_00457285_00457285
    L_0045727c:
        mov eax,dword ptr [ebp-1Ch]
    L_0045727f:
        call asm_SEH_epilog_00454bf7
    L_00457284:
        ret
    }
}
