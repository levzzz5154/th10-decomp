#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460C26..0x00460CED: ___tolower_mt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_tolower_mt_00460c26() {
    __asm {
    L_00460c26:
        push ebp
    L_00460c27:
        mov ebp,esp
    L_00460c29:
        push ecx
    L_00460c2a:
        push ebx
    L_00460c2b:
        mov ebx,dword ptr [ebp+0Ch]
    L_00460c2e:
        push esi
    L_00460c2f:
        mov esi,dword ptr [ebp+8]
    L_00460c32:
        cmp dword ptr [esi+14h],0
    L_00460c36:
        push edi
    L_00460c37:
        je asm_target_00460cda
    L_00460c3d:
        cmp dword ptr [esi+24h],0
    L_00460c41:
        je short L_00460c4c
    L_00460c43:
        cmp ebx,7Fh
    L_00460c46:
        jbe asm_target_00460cda
    L_00460c4c:
        xor edi,edi
    L_00460c4e:
        inc edi
    L_00460c4f:
        cmp ebx,100h
    L_00460c55:
        jae short L_00460c76
    L_00460c57:
        cmp dword ptr [esi+28h],edi
    L_00460c5a:
        jle short L_00460c69
    L_00460c5c:
        push edi
    L_00460c5d:
        push ebx
    L_00460c5e:
        push esi
    L_00460c5f:
        call asm_isctype_mt_00455752
    L_00460c64:
        add esp,0Ch
    L_00460c67:
        jmp short L_00460c72
    L_00460c69:
        mov eax,dword ptr [esi+48h]
    L_00460c6c:
        movzx eax,byte ptr [eax+ebx*2]
    L_00460c70:
        and eax,edi
    L_00460c72:
        test eax,eax
    L_00460c74:
        je short L_00460ce7
    L_00460c76:
        mov edx,dword ptr [esi+48h]
    L_00460c79:
        mov eax,ebx
    L_00460c7b:
        sar eax,8
    L_00460c7e:
        movzx ecx,al
    L_00460c81:
        test byte ptr [edx+ecx*2+1],80h
    L_00460c86:
        je short L_00460c97
    L_00460c88:
        push 2
    L_00460c8a:
        mov byte ptr [ebp+8],al
    L_00460c8d:
        mov byte ptr [ebp+9],bl
    L_00460c90:
        mov byte ptr [ebp+0Ah],0
    L_00460c94:
        pop eax
    L_00460c95:
        jmp short L_00460ca0
    L_00460c97:
        mov byte ptr [ebp+8],bl
    L_00460c9a:
        mov byte ptr [ebp+9],0
    L_00460c9e:
        mov eax,edi
    L_00460ca0:
        push edi
    L_00460ca1:
        push dword ptr [esi+4]
    L_00460ca4:
        lea ecx,[ebp-4]
    L_00460ca7:
        push 3
    L_00460ca9:
        push ecx
    L_00460caa:
        push eax
    L_00460cab:
        lea eax,[ebp+8]
    L_00460cae:
        push eax
    L_00460caf:
        push 100h
    L_00460cb4:
        push dword ptr [esi+14h]
    L_00460cb7:
        call asm_FUN_0045ee1d_0045ee1d
    L_00460cbc:
        add esp,20h
    L_00460cbf:
        test eax,eax
    L_00460cc1:
        je short L_00460ce7
    L_00460cc3:
        cmp eax,edi
    L_00460cc5:
        jne short L_00460ccd
    L_00460cc7:
        movzx eax,byte ptr [ebp-4]
    L_00460ccb:
        jmp short L_00460ce9
    L_00460ccd:
        movzx ecx,byte ptr [ebp-3]
    L_00460cd1:
        xor eax,eax
    L_00460cd3:
        mov ah,byte ptr [ebp-4]
    L_00460cd6:
        or eax,ecx
    L_00460cd8:
        jmp short L_00460ce9
    L_00460cda:
        cmp ebx,41h
    L_00460cdd:
        jl short L_00460ce7
    L_00460cdf:
        cmp ebx,5Ah
    L_00460ce2:
        lea eax,[ebx+20h]
    L_00460ce5:
        jle short L_00460ce9
    L_00460ce7:
        mov eax,ebx
    L_00460ce9:
        pop edi
    L_00460cea:
        pop esi
    L_00460ceb:
        pop ebx
    L_00460cec:
        leave
    L_00460ced:
        ret
    }
}
