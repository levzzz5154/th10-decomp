#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FDB8..0x0045FE46: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fdb8() {
    __asm {
    L_0045fdb8:
        push 14h
    L_0045fdba:
        push 46C910h
    L_0045fdbf:
        call asm_SEH_prolog_00454bbc
    L_0045fdc4:
        xor edi,edi
    L_0045fdc6:
        push edi
    L_0045fdc7:
        call asm_lock_00453c0c
    L_0045fdcc:
        pop ecx
    L_0045fdcd:
        mov dword ptr [ebp-4],edi
    L_0045fdd0:
        cmp dword ptr [ebp+8],edi
    L_0045fdd3:
        jne short L_0045fdee
    L_0045fdd5:
        mov dword ptr [ebp-1Ch],4776B0h
    L_0045fddc:
        mov esi,dword ptr [data_004776b0]
    L_0045fde2:
        mov dword ptr [ebp-20h],esi
    L_0045fde5:
        mov dword ptr [ebp-24h],2
    L_0045fdec:
        jmp short L_0045fe05
    L_0045fdee:
        mov dword ptr [ebp-1Ch],4776B4h
    L_0045fdf5:
        mov esi,dword ptr [data_004776b4]
    L_0045fdfb:
        mov dword ptr [ebp-20h],esi
    L_0045fdfe:
        mov dword ptr [ebp-24h],15h
    L_0045fe05:
        cmp esi,edi
    L_0045fe07:
        je short L_0045fe13
    L_0045fe09:
        cmp esi,1
    L_0045fe0c:
        je short L_0045fe13
    L_0045fe0e:
        mov eax,dword ptr [ebp-1Ch]
    L_0045fe11:
        mov dword ptr [eax],edi
    L_0045fe13:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fe17:
        call asm_target_0045fe29
    L_0045fe1c:
        cmp esi,edi
    L_0045fe1e:
        jne short L_0045fe31
    L_0045fe20:
        xor eax,eax
    L_0045fe22:
        jmp short L_0045fe3f
    L_0045fe24:
        xor edi,edi
    L_0045fe26:
        mov esi,dword ptr [ebp-20h]
    L_0045fe29:
        push edi
    L_0045fe2a:
        call asm_FUN_00453b3f_00453b3f
    L_0045fe2f:
        pop ecx
    L_0045fe30:
        ret
    L_0045fe31:
        cmp esi,1
    L_0045fe34:
        je short L_0045fe3c
    L_0045fe36:
        push dword ptr [ebp-24h]
    L_0045fe39:
        call esi
    L_0045fe3b:
        pop ecx
    L_0045fe3c:
        xor eax,eax
    L_0045fe3e:
        inc eax
    L_0045fe3f:
        call asm_SEH_epilog_00454bf7
    L_0045fe44:
        ret 4
    }
}
