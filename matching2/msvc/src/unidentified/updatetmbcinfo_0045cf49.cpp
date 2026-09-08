#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CF49..0x0045CFAB: ___updatetmbcinfo
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_updatetmbcinfo_0045cf49() {
    __asm {
    L_0045cf49:
        push 10h
    L_0045cf4b:
        push 46C538h
    L_0045cf50:
        call asm_SEH_prolog_00454bbc
    L_0045cf55:
        push 0Dh
    L_0045cf57:
        call asm_lock_00453c0c
    L_0045cf5c:
        pop ecx
    L_0045cf5d:
        and dword ptr [ebp-4],0
    L_0045cf61:
        call asm_getptd_00456357
    L_0045cf66:
        mov edi,eax
    L_0045cf68:
        mov dword ptr [ebp-20h],edi
    L_0045cf6b:
        mov esi,dword ptr [edi+60h]
    L_0045cf6e:
        mov dword ptr [ebp-1Ch],esi
    L_0045cf71:
        cmp esi,dword ptr [data_00497f94]
    L_0045cf77:
        je short L_0045cf9b
    L_0045cf79:
        test esi,esi
    L_0045cf7b:
        je short L_0045cf88
    L_0045cf7d:
        dec dword ptr [esi]
    L_0045cf7f:
        jne short L_0045cf88
    L_0045cf81:
        push esi
    L_0045cf82:
        call asm_free_00452422
    L_0045cf87:
        pop ecx
    L_0045cf88:
        mov eax,dword ptr [data_00497f94]
    L_0045cf8d:
        mov dword ptr [edi+60h],eax
    L_0045cf90:
        mov esi,dword ptr [data_00497f94]
    L_0045cf96:
        mov dword ptr [ebp-1Ch],esi
    L_0045cf99:
        inc dword ptr [esi]
    L_0045cf9b:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045cf9f:
        call asm_FUN_0045cfaf_0045cfaf
    L_0045cfa4:
        mov eax,esi
    L_0045cfa6:
        call asm_SEH_epilog_00454bf7
    L_0045cfab:
        ret
    }
}
