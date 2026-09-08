#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460D87..0x00460E40: ___dtold
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_dtold_00460d87() {
    __asm {
    L_00460d87:
        push ebp
    L_00460d88:
        mov ebp,esp
    L_00460d8a:
        push ecx
    L_00460d8b:
        mov edx,dword ptr [ebp+0Ch]
    L_00460d8e:
        xor eax,eax
    L_00460d90:
        mov ax,word ptr [edx+6]
    L_00460d94:
        push ebx
    L_00460d95:
        push esi
    L_00460d96:
        push edi
    L_00460d97:
        mov edi,7FFh
    L_00460d9c:
        mov esi,80000000h
    L_00460da1:
        mov dword ptr [ebp-4],esi
    L_00460da4:
        mov ecx,eax
    L_00460da6:
        shr ecx,4
    L_00460da9:
        and eax,8000h
    L_00460dae:
        and ecx,edi
    L_00460db0:
        mov dword ptr [ebp+0Ch],eax
    L_00460db3:
        mov eax,dword ptr [edx+4]
    L_00460db6:
        mov edx,dword ptr [edx]
    L_00460db8:
        movzx ebx,cx
    L_00460dbb:
        and eax,0FFFFFh
    L_00460dc0:
        test ebx,ebx
    L_00460dc2:
        je short L_00460dd7
    L_00460dc4:
        cmp ebx,edi
    L_00460dc6:
        je short L_00460dd0
    L_00460dc8:
        lea edi,[ecx+3C00h]
    L_00460dce:
        jmp short L_00460df8
    L_00460dd0:
        mov edi,7FFFh
    L_00460dd5:
        jmp short L_00460df8
    L_00460dd7:
        xor ebx,ebx
    L_00460dd9:
        cmp eax,ebx
    L_00460ddb:
        jne short L_00460def
    L_00460ddd:
        cmp edx,ebx
    L_00460ddf:
        jne short L_00460def
    L_00460de1:
        mov eax,dword ptr [ebp+8]
    L_00460de4:
        mov dword ptr [eax+4],ebx
    L_00460de7:
        mov dword ptr [eax],ebx
    L_00460de9:
        mov word ptr [eax+8],bx
    L_00460ded:
        jmp short L_00460e3c
    L_00460def:
        lea edi,[ecx+3C01h]
    L_00460df5:
        mov dword ptr [ebp-4],ebx
    L_00460df8:
        mov ecx,edx
    L_00460dfa:
        shr ecx,15h
    L_00460dfd:
        shl eax,0Bh
    L_00460e00:
        or ecx,eax
    L_00460e02:
        or ecx,dword ptr [ebp-4]
    L_00460e05:
        mov eax,dword ptr [ebp+8]
    L_00460e08:
        shl edx,0Bh
    L_00460e0b:
        test ecx,esi
    L_00460e0d:
        mov dword ptr [eax+4],ecx
    L_00460e10:
        mov dword ptr [eax],edx
    L_00460e12:
        jne short L_00460e33
    L_00460e14:
        mov ecx,dword ptr [eax]
    L_00460e16:
        mov edx,dword ptr [eax+4]
    L_00460e19:
        mov ebx,ecx
    L_00460e1b:
        shl edx,1
    L_00460e1d:
        shr ebx,1Fh
    L_00460e20:
        or edx,ebx
    L_00460e22:
        add ecx,ecx
    L_00460e24:
        add edi,0FFFFh
    L_00460e2a:
        test edx,esi
    L_00460e2c:
        mov dword ptr [eax+4],edx
    L_00460e2f:
        mov dword ptr [eax],ecx
    L_00460e31:
        je short L_00460e14
    L_00460e33:
        mov ecx,dword ptr [ebp+0Ch]
    L_00460e36:
        or ecx,edi
    L_00460e38:
        mov word ptr [eax+8],cx
    L_00460e3c:
        pop edi
    L_00460e3d:
        pop esi
    L_00460e3e:
        pop ebx
    L_00460e3f:
        leave
    L_00460e40:
        ret
    }
}
