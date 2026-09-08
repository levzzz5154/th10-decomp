#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A9D0..0x0044AD21: FUN_0044a9d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044a9d0_0044a9d0() {
    __asm {
    L_0044a9d0:
        sub esp,108h
    L_0044a9d6:
        mov eax,dword ptr [data_00473660]
    L_0044a9db:
        xor eax,esp
    L_0044a9dd:
        push esi
    L_0044a9de:
        mov esi,ecx
    L_0044a9e0:
        imul esi,6Ah
    L_0044a9e3:
        mov dword ptr [esp+108h],eax
    L_0044a9ea:
        mov eax,dword ptr [data_004924fc]
    L_0044a9ef:
        push edi
    L_0044a9f0:
        xor edi,edi
    L_0044a9f2:
        add esi,474E30h
    L_0044a9f8:
        test eax,eax
    L_0044a9fa:
        je asm_target_0044ac90
    L_0044aa00:
        mov eax,dword ptr [data_00491ff4]
    L_0044aa05:
        test ah,2
    L_0044aa08:
        jne asm_target_0044ab31
    L_0044aa0e:
        lea eax,[esp+0Ch]
    L_0044aa12:
        push eax
    L_0044aa13:
        call dword ptr [data_00466208]
    L_0044aa19:
        mov al,byte ptr [esp+1Ch]
    L_0044aa1d:
        mov cl,byte ptr [esp+64h]
    L_0044aa21:
        mov dl,byte ptr [esp+66h]
    L_0044aa25:
        and cl,0BFh
    L_0044aa28:
        shr dl,1
    L_0044aa2a:
        or cl,dl
    L_0044aa2c:
        mov dl,byte ptr [esp+27h]
    L_0044aa30:
        shr cl,1
    L_0044aa32:
        and al,9Fh
    L_0044aa34:
        or cl,al
    L_0044aa36:
        mov al,byte ptr [esp+74h]
    L_0044aa3a:
        shr cl,1
    L_0044aa3c:
        and dl,8Fh
    L_0044aa3f:
        or cl,dl
    L_0044aa41:
        or al,byte ptr [esp+32h]
    L_0044aa45:
        mov dl,byte ptr [esp+6Eh]
    L_0044aa49:
        shr cl,1
    L_0044aa4b:
        and al,87h
    L_0044aa4d:
        or cl,al
    L_0044aa4f:
        or dl,byte ptr [esp+34h]
    L_0044aa53:
        mov al,byte ptr [esp+70h]
    L_0044aa57:
        shr cl,1
    L_0044aa59:
        and dl,83h
    L_0044aa5c:
        or cl,dl
    L_0044aa5e:
        or al,byte ptr [esp+31h]
    L_0044aa62:
        mov dl,byte ptr [esp+72h]
    L_0044aa66:
        shr cl,1
    L_0044aa68:
        and al,81h
    L_0044aa6a:
        or cl,al
    L_0044aa6c:
        or dl,byte ptr [esp+33h]
    L_0044aa70:
        mov al,byte ptr [esp+5Eh]
    L_0044aa74:
        shr cl,1
    L_0044aa76:
        and dl,80h
    L_0044aa79:
        or cl,dl
    L_0044aa7b:
        mov dl,byte ptr [esp+50h]
    L_0044aa7f:
        movzx di,cl
    L_0044aa83:
        and al,80h
    L_0044aa85:
        and dl,80h
    L_0044aa88:
        movzx cx,al
    L_0044aa8c:
        movzx ax,dl
    L_0044aa90:
        mov dl,byte ptr [esp+19h]
    L_0044aa94:
        and dl,80h
    L_0044aa97:
        shl ecx,1
    L_0044aa99:
        or ecx,eax
    L_0044aa9b:
        movzx ax,dl
    L_0044aa9f:
        mov dl,byte ptr [esp+5Ch]
    L_0044aaa3:
        shl ecx,1
    L_0044aaa5:
        or ecx,eax
    L_0044aaa7:
        or dl,byte ptr [esp+30h]
    L_0044aaab:
        and dl,80h
    L_0044aaae:
        movzx ax,dl
    L_0044aab2:
        mov dl,byte ptr [esp+5Fh]
    L_0044aab6:
        shl ecx,1
    L_0044aab8:
        and dl,80h
    L_0044aabb:
        or ecx,eax
    L_0044aabd:
        movzx ax,dl
    L_0044aac1:
        mov dl,byte ptr [esp+5Dh]
    L_0044aac5:
        shl ecx,1
    L_0044aac7:
        and dl,80h
    L_0044aaca:
        or ecx,eax
    L_0044aacc:
        movzx ax,dl
    L_0044aad0:
        mov dl,byte ptr [esp+1Dh]
    L_0044aad4:
        shl ecx,1
    L_0044aad6:
        and dl,80h
    L_0044aad9:
        or ecx,eax
    L_0044aadb:
        movzx ax,dl
    L_0044aadf:
        shl ecx,1
    L_0044aae1:
        or ecx,eax
    L_0044aae3:
        shl ecx,1
    L_0044aae5:
        or edi,ecx
    L_0044aae7:
        mov cl,byte ptr [esp+6Fh]
    L_0044aaeb:
        and cl,80h
    L_0044aaee:
        neg cl
    L_0044aaf0:
        mov dl,byte ptr [esp+75h]
    L_0044aaf4:
        mov al,byte ptr [esp+6Dh]
    L_0044aaf8:
        sbb ecx,ecx
    L_0044aafa:
        and ecx,0A0h
    L_0044ab00:
        or edi,ecx
    L_0044ab02:
        mov cl,byte ptr [esp+73h]
    L_0044ab06:
        and dl,80h
    L_0044ab09:
        neg dl
    L_0044ab0b:
        sbb edx,edx
    L_0044ab0d:
        and edx,90h
    L_0044ab13:
        and al,80h
    L_0044ab15:
        or edi,edx
    L_0044ab17:
        neg al
    L_0044ab19:
        sbb eax,eax
    L_0044ab1b:
        and eax,60h
    L_0044ab1e:
        and cl,80h
    L_0044ab21:
        or edi,eax
    L_0044ab23:
        neg cl
    L_0044ab25:
        sbb ecx,ecx
    L_0044ab27:
        and ecx,50h
    L_0044ab2a:
        or edi,ecx
    L_0044ab2c:
        jmp asm_target_0044ac90
    L_0044ab31:
        mov eax,dword ptr [data_00491c38]
    L_0044ab36:
        mov edx,dword ptr [eax]
    L_0044ab38:
        lea ecx,[esp+0Ch]
    L_0044ab3c:
        push ecx
    L_0044ab3d:
        push 100h
    L_0044ab42:
        push eax
    L_0044ab43:
        call dword ptr [edx+24h]
    L_0044ab46:
        xor edi,edi
    L_0044ab48:
        cmp eax,8007001Eh
    L_0044ab4d:
        jne short L_0044ab5f
    L_0044ab4f:
        mov eax,dword ptr [data_00491c38]
    L_0044ab54:
        mov edx,dword ptr [eax]
    L_0044ab56:
        push eax
    L_0044ab57:
        call dword ptr [edx+1Ch]
    L_0044ab5a:
        jmp asm_target_0044ac90
    L_0044ab5f:
        test eax,eax
    L_0044ab61:
        je short L_0044ab73
    L_0044ab63:
        mov eax,dword ptr [data_00491c38]
    L_0044ab68:
        mov ecx,dword ptr [eax]
    L_0044ab6a:
        push eax
    L_0044ab6b:
        call dword ptr [ecx+1Ch]
    L_0044ab6e:
        jmp asm_target_0044ac90
    L_0044ab73:
        mov cl,byte ptr [esp+36h]
    L_0044ab77:
        mov dl,byte ptr [esp+39h]
    L_0044ab7b:
        mov al,byte ptr [esp+38h]
    L_0044ab7f:
        and dl,0BFh
    L_0044ab82:
        shr al,1
    L_0044ab84:
        or dl,al
    L_0044ab86:
        shr dl,1
    L_0044ab88:
        mov al,byte ptr [esp+0Dh]
    L_0044ab8c:
        and cl,9Fh
    L_0044ab8f:
        or dl,cl
    L_0044ab91:
        mov cl,byte ptr [esp+54h]
    L_0044ab95:
        shr dl,1
    L_0044ab97:
        and al,8Fh
    L_0044ab99:
        or dl,al
    L_0044ab9b:
        or cl,byte ptr [esp+0D4h]
    L_0044aba2:
        mov al,byte ptr [esp+0DCh]
    L_0044aba9:
        shr dl,1
    L_0044abab:
        and cl,87h
    L_0044abae:
        or dl,cl
    L_0044abb0:
        or al,byte ptr [esp+5Ch]
    L_0044abb4:
        mov cl,byte ptr [esp+57h]
    L_0044abb8:
        shr dl,1
    L_0044abba:
        and al,83h
    L_0044abbc:
        or dl,al
    L_0044abbe:
        or cl,byte ptr [esp+0D7h]
    L_0044abc5:
        mov al,byte ptr [esp+59h]
    L_0044abc9:
        shr dl,1
    L_0044abcb:
        and cl,81h
    L_0044abce:
        or dl,cl
    L_0044abd0:
        or al,byte ptr [esp+0D9h]
    L_0044abd7:
        mov cl,byte ptr [esp+1Fh]
    L_0044abdb:
        shr dl,1
    L_0044abdd:
        and al,80h
    L_0044abdf:
        or dl,al
    L_0044abe1:
        mov al,byte ptr [esp+2Ch]
    L_0044abe5:
        movzx di,dl
    L_0044abe9:
        and cl,80h
    L_0044abec:
        and al,80h
    L_0044abee:
        movzx dx,cl
    L_0044abf2:
        movzx cx,al
    L_0044abf6:
        mov al,byte ptr [esp+28h]
    L_0044abfa:
        and al,80h
    L_0044abfc:
        shl edx,1
    L_0044abfe:
        or edx,ecx
    L_0044ac00:
        movzx cx,al
    L_0044ac04:
        mov al,byte ptr [esp+25h]
    L_0044ac08:
        shl edx,1
    L_0044ac0a:
        or edx,ecx
    L_0044ac0c:
        or al,byte ptr [esp+0D3h]
    L_0044ac13:
        and al,80h
    L_0044ac15:
        movzx cx,al
    L_0044ac19:
        mov al,byte ptr [esp+2Bh]
    L_0044ac1d:
        shl edx,1
    L_0044ac1f:
        and al,80h
    L_0044ac21:
        or edx,ecx
    L_0044ac23:
        movzx cx,al
    L_0044ac27:
        mov al,byte ptr [esp+1Ch]
    L_0044ac2b:
        shl edx,1
    L_0044ac2d:
        and al,80h
    L_0044ac2f:
        or edx,ecx
    L_0044ac31:
        movzx cx,al
    L_0044ac35:
        mov al,byte ptr [esp+29h]
    L_0044ac39:
        shl edx,1
    L_0044ac3b:
        and al,80h
    L_0044ac3d:
        or edx,ecx
    L_0044ac3f:
        movzx cx,al
    L_0044ac43:
        shl edx,1
    L_0044ac45:
        or edx,ecx
    L_0044ac47:
        shl edx,1
    L_0044ac49:
        or edi,edx
    L_0044ac4b:
        mov dl,byte ptr [esp+55h]
    L_0044ac4f:
        and dl,80h
    L_0044ac52:
        neg dl
    L_0044ac54:
        sbb edx,edx
    L_0044ac56:
        and edx,90h
    L_0044ac5c:
        or edi,edx
    L_0044ac5e:
        mov al,byte ptr [esp+5Bh]
    L_0044ac62:
        mov cl,byte ptr [esp+53h]
    L_0044ac66:
        mov dl,byte ptr [esp+5Dh]
    L_0044ac6a:
        and al,80h
    L_0044ac6c:
        neg al
    L_0044ac6e:
        sbb eax,eax
    L_0044ac70:
        and eax,60h
    L_0044ac73:
        and cl,80h
    L_0044ac76:
        or edi,eax
    L_0044ac78:
        neg cl
    L_0044ac7a:
        sbb ecx,ecx
    L_0044ac7c:
        and ecx,50h
    L_0044ac7f:
        and dl,80h
    L_0044ac82:
        or edi,ecx
    L_0044ac84:
        neg dl
    L_0044ac86:
        sbb edx,edx
    L_0044ac88:
        and edx,0A0h
    L_0044ac8e:
        or edi,edx
    L_0044ac90:
        push 0
    L_0044ac92:
        push 0
    L_0044ac94:
        mov ecx,edi
    L_0044ac96:
        call asm_FUN_0044a190_0044a190
    L_0044ac9b:
        mov cx,word ptr [esi]
    L_0044ac9e:
        mov word ptr [esi+2],cx
    L_0044aca2:
        mov word ptr [esi],ax
    L_0044aca5:
        mov edx,1
    L_0044acaa:
        mov word ptr [esi+4],0
    L_0044acb0:
        mov dword ptr [esp+8],eax
    L_0044acb4:
        lea ecx,[esi+0Ah]
    L_0044acb7:
        mov edi,10h
    L_0044acbc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0044acc0:
        test byte ptr [esp+8],1
    L_0044acc5:
        je short L_0044acdb
    L_0044acc7:
        inc word ptr [ecx]
    L_0044acca:
        cmp word ptr [ecx],1Ah
    L_0044acce:
        jb short L_0044ace0
    L_0044acd0:
        or word ptr [esi+4],dx
    L_0044acd4:
        TH10_ADD_M16_IMM16(TH10_R32_ECX, 0xfff8)
    L_0044acd9:
        jmp short L_0044ace0
    L_0044acdb:
        mov word ptr [ecx],0
    L_0044ace0:
        shr word ptr [esp+8],1
    L_0044ace5:
        add ecx,2
    L_0044ace8:
        shl edx,1
    L_0044acea:
        dec edi
    L_0044aceb:
        jne short L_0044acc0
    L_0044aced:
        xor ecx,ecx
    L_0044acef:
        mov cx,word ptr [esi]
    L_0044acf2:
        xor edx,edx
    L_0044acf4:
        mov dx,word ptr [esi+2]
    L_0044acf8:
        xor dx,cx
    L_0044acfb:
        mov edi,edx
    L_0044acfd:
        and edi,ecx
    L_0044acff:
        not ecx
    L_0044ad01:
        and ecx,edx
    L_0044ad03:
        mov word ptr [esi+6],di
    L_0044ad07:
        mov word ptr [esi+8],cx
    L_0044ad0b:
        mov ecx,dword ptr [esp+10Ch]
    L_0044ad12:
        pop edi
    L_0044ad13:
        pop esi
    L_0044ad14:
        xor ecx,esp
    L_0044ad16:
        call asm_security_check_cookie_00458ea5
    L_0044ad1b:
        add esp,108h
    L_0044ad21:
        ret
    }
}
