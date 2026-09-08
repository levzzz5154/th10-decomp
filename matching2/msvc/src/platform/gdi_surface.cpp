#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436AF0..0x00436C94: FUN_00436af0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436af0_00436af0() {
    __asm {
    L_00436af0:
        sub esp,70h
    L_00436af3:
        push ebp
    L_00436af4:
        push esi
    L_00436af5:
        push edi
    L_00436af6:
        mov esi,eax
    L_00436af8:
        call asm_FontCache_FlushRetail_00436a30
    L_00436afd:
        xor eax,eax
    L_00436aff:
        mov ecx,1Bh
    L_00436b04:
        lea edi,[esp+10h]
    L_00436b08:
        rep stosd
    L_00436b0a:
        mov ecx,dword ptr [data_00474918]
    L_00436b10:
        cmp ecx,0FFFFFFFFh
    L_00436b13:
        je short L_00436b32
    L_00436b15:
        mov ebp,dword ptr [esp+88h]
    L_00436b1c:
        cmp ecx,ebp
    L_00436b1e:
        je short L_00436b39
    L_00436b20:
        inc eax
    L_00436b21:
        lea ecx,[eax+eax*2]
    L_00436b24:
        mov ecx,dword ptr [ecx*8+474918h]
    L_00436b2b:
        cmp ecx,0FFFFFFFFh
    L_00436b2e:
        jne short L_00436b15
    L_00436b30:
        jmp short L_00436b39
    L_00436b32:
        mov ebp,dword ptr [esp+88h]
    L_00436b39:
        cmp ebp,0FFFFFFFFh
    L_00436b3c:
        je short L_00436b4c
    L_00436b3e:
        lea ecx,[eax+eax*2]
    L_00436b41:
        lea ecx,[ecx*8+474918h]
    L_00436b48:
        test ecx,ecx
    L_00436b4a:
        jne short L_00436b57
    L_00436b4c:
        pop edi
    L_00436b4d:
        pop esi
    L_00436b4e:
        xor al,al
    L_00436b50:
        pop ebp
    L_00436b51:
        add esp,70h
    L_00436b54:
        ret 0Ch
    L_00436b57:
        mov edi,dword ptr [esp+80h]
    L_00436b5e:
        mov eax,dword ptr [ecx+4]
    L_00436b61:
        imul eax,edi
    L_00436b64:
        cdq
    L_00436b65:
        and edx,7
    L_00436b68:
        add eax,edx
    L_00436b6a:
        sar eax,3
    L_00436b6d:
        add eax,3
    L_00436b70:
        cdq
    L_00436b71:
        and edx,3
    L_00436b74:
        add eax,edx
    L_00436b76:
        push ebx
    L_00436b77:
        or edx,0FFFFFFFFh
    L_00436b7a:
        mov ebx,eax
    L_00436b7c:
        mov eax,dword ptr [esp+88h]
    L_00436b83:
        sub edx,eax
    L_00436b85:
        mov dword ptr [esp+1Ch],edx
    L_00436b89:
        mov dx,word ptr [ecx+4]
    L_00436b8d:
        sar ebx,2
    L_00436b90:
        shl ebx,2
    L_00436b93:
        mov word ptr [esp+22h],dx
    L_00436b98:
        mov edx,ebx
    L_00436b9a:
        imul edx,eax
    L_00436b9d:
        cmp ebp,18h
    L_00436ba0:
        mov dword ptr [esp+14h],6Ch
    L_00436ba8:
        mov dword ptr [esp+18h],edi
    L_00436bac:
        mov word ptr [esp+20h],1
    L_00436bb3:
        mov dword ptr [esp+28h],edx
    L_00436bb7:
        je short L_00436be2
    L_00436bb9:
        cmp ebp,16h
    L_00436bbc:
        je short L_00436be2
    L_00436bbe:
        mov eax,dword ptr [ecx+0Ch]
    L_00436bc1:
        mov edx,dword ptr [ecx+10h]
    L_00436bc4:
        mov dword ptr [esp+3Ch],eax
    L_00436bc8:
        mov eax,dword ptr [ecx+14h]
    L_00436bcb:
        mov ecx,dword ptr [ecx+8]
    L_00436bce:
        mov dword ptr [esp+24h],3
    L_00436bd6:
        mov dword ptr [esp+40h],edx
    L_00436bda:
        mov dword ptr [esp+44h],eax
    L_00436bde:
        mov dword ptr [esp+48h],ecx
    L_00436be2:
        push 0
    L_00436be4:
        push 0
    L_00436be6:
        lea edx,[esp+18h]
    L_00436bea:
        push edx
    L_00436beb:
        push 0
    L_00436bed:
        lea eax,[esp+24h]
    L_00436bf1:
        push eax
    L_00436bf2:
        push 0
    L_00436bf4:
        call dword ptr [data_00466024]
    L_00436bfa:
        mov ebp,eax
    L_00436bfc:
        test ebp,ebp
    L_00436bfe:
        jne short L_00436c0c
    L_00436c00:
        pop ebx
    L_00436c01:
        pop edi
    L_00436c02:
        pop esi
    L_00436c03:
        xor al,al
    L_00436c05:
        pop ebp
    L_00436c06:
        add esp,70h
    L_00436c09:
        ret 0Ch
    L_00436c0c:
        mov ecx,dword ptr [esp+28h]
    L_00436c10:
        mov edi,dword ptr [esp+10h]
    L_00436c14:
        mov edx,ecx
    L_00436c16:
        shr ecx,2
    L_00436c19:
        xor eax,eax
    L_00436c1b:
        rep stosd
    L_00436c1d:
        mov ecx,edx
    L_00436c1f:
        and ecx,3
    L_00436c22:
        push 0
    L_00436c24:
        rep stosb
    L_00436c26:
        call dword ptr [data_00466020]
    L_00436c2c:
        mov edi,eax
    L_00436c2e:
        push ebp
    L_00436c2f:
        push edi
    L_00436c30:
        call dword ptr [data_0046602c]
    L_00436c36:
        mov ecx,dword ptr [esp+10h]
    L_00436c3a:
        mov edx,dword ptr [esp+28h]
    L_00436c3e:
        mov dword ptr [esi+118h],eax
    L_00436c44:
        mov eax,dword ptr [esp+84h]
    L_00436c4b:
        mov dword ptr [esi+110h],ebx
    L_00436c51:
        pop ebx
    L_00436c52:
        mov dword ptr [esi+120h],ecx
    L_00436c58:
        mov ecx,dword ptr [esp+84h]
    L_00436c5f:
        mov dword ptr [esi+10Ch],edx
    L_00436c65:
        mov edx,dword ptr [esp+88h]
    L_00436c6c:
        mov dword ptr [esi+114h],edi
    L_00436c72:
        pop edi
    L_00436c73:
        mov dword ptr [esi+11Ch],ebp
    L_00436c79:
        mov dword ptr [esi+104h],eax
    L_00436c7f:
        mov dword ptr [esi+108h],ecx
    L_00436c85:
        mov dword ptr [esi+100h],edx
    L_00436c8b:
        pop esi
    L_00436c8c:
        mov al,1
    L_00436c8e:
        pop ebp
    L_00436c8f:
        add esp,70h
    L_00436c92:
        ret 0Ch
    }
}
