#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FD56..0x0045FDA5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fd56() {
    __asm {
    L_0045fd56:
        push 0Ch
    L_0045fd58:
        push 46C900h
    L_0045fd5d:
        call asm_SEH_prolog_00454bbc
    L_0045fd62:
        xor esi,esi
    L_0045fd64:
        cmp dword ptr [ebp+8],esi
    L_0045fd67:
        jne short L_0045fd72
    L_0045fd69:
        push esi
    L_0045fd6a:
        call asm_flsall_0045fc81
    L_0045fd6f:
        pop ecx
    L_0045fd70:
        jmp short L_0045fd96
    L_0045fd72:
        push dword ptr [ebp+8]
    L_0045fd75:
        call asm_target_0045a06a
    L_0045fd7a:
        pop ecx
    L_0045fd7b:
        mov dword ptr [ebp-4],esi
    L_0045fd7e:
        push dword ptr [ebp+8]
    L_0045fd81:
        call asm_fflush_lk_0045fc53
    L_0045fd86:
        pop ecx
    L_0045fd87:
        mov dword ptr [ebp-1Ch],eax
    L_0045fd8a:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fd8e:
        call asm_target_0045fd9c
    L_0045fd93:
        mov eax,dword ptr [ebp-1Ch]
    L_0045fd96:
        call asm_SEH_epilog_00454bf7
    L_0045fd9b:
        ret
    L_0045fd9c:
        push dword ptr [ebp+8]
    L_0045fd9f:
        call asm_unassigned_0045a0bc
    L_0045fda4:
        pop ecx
    L_0045fda5:
        ret
    }
}
