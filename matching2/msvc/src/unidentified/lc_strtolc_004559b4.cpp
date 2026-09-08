#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004559B4..0x00455A8F: ___lc_strtolc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lc_strtolc_004559b4() {
    __asm {
    L_004559b4:
        push ebp
    L_004559b5:
        mov ebp,esp
    L_004559b7:
        push esi
    L_004559b8:
        push edi
    L_004559b9:
        mov edi,dword ptr [ebp+8]
    L_004559bc:
        push 90h
    L_004559c1:
        push 0
    L_004559c3:
        push edi
    L_004559c4:
        call asm_memset_0045bed0
    L_004559c9:
        mov esi,dword ptr [ebp+0Ch]
    L_004559cc:
        mov al,byte ptr [esi]
    L_004559ce:
        add esp,0Ch
    L_004559d1:
        test al,al
    L_004559d3:
        je short L_004559fa
    L_004559d5:
        cmp al,2Eh
    L_004559d7:
        jne short L_00455a01
    L_004559d9:
        lea eax,[esi+1]
    L_004559dc:
        cmp byte ptr [eax],0
    L_004559df:
        je short L_00455a01
    L_004559e1:
        push 0Fh
    L_004559e3:
        push eax
    L_004559e4:
        lea eax,[edi+80h]
    L_004559ea:
        push eax
    L_004559eb:
        call asm_strncpy_00452960
    L_004559f0:
        add esp,0Ch
    L_004559f3:
        mov byte ptr [edi+8Fh],0
    L_004559fa:
        xor eax,eax
    L_004559fc:
        jmp asm_target_00455a88
    L_00455a01:
        and dword ptr [ebp+0Ch],0
    L_00455a05:
        push ebx
    L_00455a06:
        jmp short L_00455a73
    L_00455a08:
        cmp dword ptr [ebp+0Ch],0
    L_00455a0c:
        lea edi,[eax+esi]
    L_00455a0f:
        mov bl,byte ptr [edi]
    L_00455a11:
        jne short L_00455a24
    L_00455a13:
        cmp eax,40h
    L_00455a16:
        jae short L_00455a84
    L_00455a18:
        cmp bl,2Eh
    L_00455a1b:
        je short L_00455a84
    L_00455a1d:
        push eax
    L_00455a1e:
        push esi
    L_00455a1f:
        push dword ptr [ebp+8]
    L_00455a22:
        jmp short L_00455a5c
    L_00455a24:
        cmp dword ptr [ebp+0Ch],1
    L_00455a28:
        jne short L_00455a3d
    L_00455a2a:
        cmp eax,40h
    L_00455a2d:
        jae short L_00455a84
    L_00455a2f:
        cmp bl,5Fh
    L_00455a32:
        je short L_00455a84
    L_00455a34:
        push eax
    L_00455a35:
        mov eax,dword ptr [ebp+8]
    L_00455a38:
        add eax,40h
    L_00455a3b:
        jmp short L_00455a5a
    L_00455a3d:
        cmp dword ptr [ebp+0Ch],2
    L_00455a41:
        jne short L_00455a84
    L_00455a43:
        cmp eax,10h
    L_00455a46:
        jae short L_00455a84
    L_00455a48:
        test bl,bl
    L_00455a4a:
        je short L_00455a51
    L_00455a4c:
        cmp bl,2Ch
    L_00455a4f:
        jne short L_00455a84
    L_00455a51:
        push eax
    L_00455a52:
        mov eax,dword ptr [ebp+8]
    L_00455a55:
        add eax,80h
    L_00455a5a:
        push esi
    L_00455a5b:
        push eax
    L_00455a5c:
        call asm_strncpy_00452960
    L_00455a61:
        add esp,0Ch
    L_00455a64:
        cmp bl,2Ch
    L_00455a67:
        je short L_00455a8c
    L_00455a69:
        test bl,bl
    L_00455a6b:
        je short L_00455a8c
    L_00455a6d:
        inc dword ptr [ebp+0Ch]
    L_00455a70:
        lea esi,[edi+1]
    L_00455a73:
        push 46A9E8h
    L_00455a78:
        push esi
    L_00455a79:
        call asm_strcspn_0045be80
    L_00455a7e:
        test eax,eax
    L_00455a80:
        pop ecx
    L_00455a81:
        pop ecx
    L_00455a82:
        jne short L_00455a08
    L_00455a84:
        or eax,0FFFFFFFFh
    L_00455a87:
        pop ebx
    L_00455a88:
        pop edi
    L_00455a89:
        pop esi
    L_00455a8a:
        pop ebp
    L_00455a8b:
        ret
    L_00455a8c:
        xor eax,eax
    L_00455a8e:
        jmp short L_00455a87
    }
}
