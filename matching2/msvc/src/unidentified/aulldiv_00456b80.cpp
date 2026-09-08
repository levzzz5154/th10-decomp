#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456B80..0x00456BE7: __aulldiv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_aulldiv_00456b80() {
    __asm {
    L_00456b80:
        push ebx
    L_00456b81:
        push esi
    L_00456b82:
        mov eax,dword ptr [esp+18h]
    L_00456b86:
        or eax,eax
    L_00456b88:
        jne short L_00456ba2
    L_00456b8a:
        mov ecx,dword ptr [esp+14h]
    L_00456b8e:
        mov eax,dword ptr [esp+10h]
    L_00456b92:
        xor edx,edx
    L_00456b94:
        div ecx
    L_00456b96:
        mov ebx,eax
    L_00456b98:
        mov eax,dword ptr [esp+0Ch]
    L_00456b9c:
        div ecx
    L_00456b9e:
        mov edx,ebx
    L_00456ba0:
        jmp short L_00456be3
    L_00456ba2:
        mov ecx,eax
    L_00456ba4:
        mov ebx,dword ptr [esp+14h]
    L_00456ba8:
        mov edx,dword ptr [esp+10h]
    L_00456bac:
        mov eax,dword ptr [esp+0Ch]
    L_00456bb0:
        shr ecx,1
    L_00456bb2:
        rcr ebx,1
    L_00456bb4:
        shr edx,1
    L_00456bb6:
        rcr eax,1
    L_00456bb8:
        or ecx,ecx
    L_00456bba:
        jne short L_00456bb0
    L_00456bbc:
        div ebx
    L_00456bbe:
        mov esi,eax
    L_00456bc0:
        mul dword ptr [esp+18h]
    L_00456bc4:
        mov ecx,eax
    L_00456bc6:
        mov eax,dword ptr [esp+14h]
    L_00456bca:
        mul esi
    L_00456bcc:
        add edx,ecx
    L_00456bce:
        jb short L_00456bde
    L_00456bd0:
        cmp edx,dword ptr [esp+10h]
    L_00456bd4:
        ja short L_00456bde
    L_00456bd6:
        jb short L_00456bdf
    L_00456bd8:
        cmp eax,dword ptr [esp+0Ch]
    L_00456bdc:
        jbe short L_00456bdf
    L_00456bde:
        dec esi
    L_00456bdf:
        xor edx,edx
    L_00456be1:
        mov eax,esi
    L_00456be3:
        pop esi
    L_00456be4:
        pop ebx
    L_00456be5:
        ret 10h
    }
}
