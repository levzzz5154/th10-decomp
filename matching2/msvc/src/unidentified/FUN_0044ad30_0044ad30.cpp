#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044AD30..0x0044B004: FUN_0044ad30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044ad30_0044ad30() {
    __asm {
    L_0044ad30:
        sub esp,104h
    L_0044ad36:
        mov eax,dword ptr [data_00473660]
    L_0044ad3b:
        xor eax,esp
    L_0044ad3d:
        mov dword ptr [esp+100h],eax
    L_0044ad44:
        mov eax,dword ptr [data_004924fc]
    L_0044ad49:
        push esi
    L_0044ad4a:
        xor esi,esi
    L_0044ad4c:
        test eax,eax
    L_0044ad4e:
        je asm_target_0044afe4
    L_0044ad54:
        mov eax,dword ptr [data_00491ff4]
    L_0044ad59:
        test ah,2
    L_0044ad5c:
        jne asm_target_0044ae85
    L_0044ad62:
        lea eax,[esp+4]
    L_0044ad66:
        push eax
    L_0044ad67:
        call dword ptr [data_00466208]
    L_0044ad6d:
        mov al,byte ptr [esp+14h]
    L_0044ad71:
        mov cl,byte ptr [esp+5Ch]
    L_0044ad75:
        mov dl,byte ptr [esp+5Eh]
    L_0044ad79:
        and cl,0BFh
    L_0044ad7c:
        shr dl,1
    L_0044ad7e:
        or cl,dl
    L_0044ad80:
        mov dl,byte ptr [esp+1Fh]
    L_0044ad84:
        shr cl,1
    L_0044ad86:
        and al,9Fh
    L_0044ad88:
        or cl,al
    L_0044ad8a:
        mov al,byte ptr [esp+6Ch]
    L_0044ad8e:
        shr cl,1
    L_0044ad90:
        and dl,8Fh
    L_0044ad93:
        or cl,dl
    L_0044ad95:
        or al,byte ptr [esp+2Ah]
    L_0044ad99:
        mov dl,byte ptr [esp+66h]
    L_0044ad9d:
        shr cl,1
    L_0044ad9f:
        and al,87h
    L_0044ada1:
        or cl,al
    L_0044ada3:
        or dl,byte ptr [esp+2Ch]
    L_0044ada7:
        mov al,byte ptr [esp+68h]
    L_0044adab:
        shr cl,1
    L_0044adad:
        and dl,83h
    L_0044adb0:
        or cl,dl
    L_0044adb2:
        or al,byte ptr [esp+29h]
    L_0044adb6:
        mov dl,byte ptr [esp+6Ah]
    L_0044adba:
        shr cl,1
    L_0044adbc:
        and al,81h
    L_0044adbe:
        or cl,al
    L_0044adc0:
        or dl,byte ptr [esp+2Bh]
    L_0044adc4:
        mov al,byte ptr [esp+56h]
    L_0044adc8:
        shr cl,1
    L_0044adca:
        and dl,80h
    L_0044adcd:
        or cl,dl
    L_0044adcf:
        mov dl,byte ptr [esp+48h]
    L_0044add3:
        movzx si,cl
    L_0044add7:
        and al,80h
    L_0044add9:
        and dl,80h
    L_0044addc:
        movzx cx,al
    L_0044ade0:
        movzx ax,dl
    L_0044ade4:
        mov dl,byte ptr [esp+11h]
    L_0044ade8:
        and dl,80h
    L_0044adeb:
        shl ecx,1
    L_0044aded:
        or ecx,eax
    L_0044adef:
        movzx ax,dl
    L_0044adf3:
        mov dl,byte ptr [esp+54h]
    L_0044adf7:
        shl ecx,1
    L_0044adf9:
        or ecx,eax
    L_0044adfb:
        or dl,byte ptr [esp+28h]
    L_0044adff:
        and dl,80h
    L_0044ae02:
        movzx ax,dl
    L_0044ae06:
        mov dl,byte ptr [esp+57h]
    L_0044ae0a:
        shl ecx,1
    L_0044ae0c:
        and dl,80h
    L_0044ae0f:
        or ecx,eax
    L_0044ae11:
        movzx ax,dl
    L_0044ae15:
        mov dl,byte ptr [esp+55h]
    L_0044ae19:
        shl ecx,1
    L_0044ae1b:
        and dl,80h
    L_0044ae1e:
        or ecx,eax
    L_0044ae20:
        movzx ax,dl
    L_0044ae24:
        mov dl,byte ptr [esp+15h]
    L_0044ae28:
        shl ecx,1
    L_0044ae2a:
        and dl,80h
    L_0044ae2d:
        or ecx,eax
    L_0044ae2f:
        movzx ax,dl
    L_0044ae33:
        shl ecx,1
    L_0044ae35:
        or ecx,eax
    L_0044ae37:
        shl ecx,1
    L_0044ae39:
        or esi,ecx
    L_0044ae3b:
        mov cl,byte ptr [esp+67h]
    L_0044ae3f:
        and cl,80h
    L_0044ae42:
        neg cl
    L_0044ae44:
        mov dl,byte ptr [esp+6Dh]
    L_0044ae48:
        mov al,byte ptr [esp+65h]
    L_0044ae4c:
        sbb ecx,ecx
    L_0044ae4e:
        and ecx,0A0h
    L_0044ae54:
        or esi,ecx
    L_0044ae56:
        mov cl,byte ptr [esp+6Bh]
    L_0044ae5a:
        and dl,80h
    L_0044ae5d:
        neg dl
    L_0044ae5f:
        sbb edx,edx
    L_0044ae61:
        and edx,90h
    L_0044ae67:
        and al,80h
    L_0044ae69:
        or esi,edx
    L_0044ae6b:
        neg al
    L_0044ae6d:
        sbb eax,eax
    L_0044ae6f:
        and eax,60h
    L_0044ae72:
        and cl,80h
    L_0044ae75:
        or esi,eax
    L_0044ae77:
        neg cl
    L_0044ae79:
        sbb ecx,ecx
    L_0044ae7b:
        and ecx,50h
    L_0044ae7e:
        or esi,ecx
    L_0044ae80:
        jmp asm_target_0044afe4
    L_0044ae85:
        mov eax,dword ptr [data_00491c38]
    L_0044ae8a:
        mov edx,dword ptr [eax]
    L_0044ae8c:
        lea ecx,[esp+4]
    L_0044ae90:
        push ecx
    L_0044ae91:
        push 100h
    L_0044ae96:
        push eax
    L_0044ae97:
        call dword ptr [edx+24h]
    L_0044ae9a:
        xor esi,esi
    L_0044ae9c:
        cmp eax,8007001Eh
    L_0044aea1:
        jne short L_0044aeb3
    L_0044aea3:
        mov eax,dword ptr [data_00491c38]
    L_0044aea8:
        mov edx,dword ptr [eax]
    L_0044aeaa:
        push eax
    L_0044aeab:
        call dword ptr [edx+1Ch]
    L_0044aeae:
        jmp asm_target_0044afe4
    L_0044aeb3:
        test eax,eax
    L_0044aeb5:
        je short L_0044aec7
    L_0044aeb7:
        mov eax,dword ptr [data_00491c38]
    L_0044aebc:
        mov ecx,dword ptr [eax]
    L_0044aebe:
        push eax
    L_0044aebf:
        call dword ptr [ecx+1Ch]
    L_0044aec2:
        jmp asm_target_0044afe4
    L_0044aec7:
        mov cl,byte ptr [esp+2Eh]
    L_0044aecb:
        mov dl,byte ptr [esp+31h]
    L_0044aecf:
        mov al,byte ptr [esp+30h]
    L_0044aed3:
        and dl,0BFh
    L_0044aed6:
        shr al,1
    L_0044aed8:
        or dl,al
    L_0044aeda:
        shr dl,1
    L_0044aedc:
        mov al,byte ptr [esp+5]
    L_0044aee0:
        and cl,9Fh
    L_0044aee3:
        or dl,cl
    L_0044aee5:
        mov cl,byte ptr [esp+4Ch]
    L_0044aee9:
        shr dl,1
    L_0044aeeb:
        and al,8Fh
    L_0044aeed:
        or dl,al
    L_0044aeef:
        or cl,byte ptr [esp+0CCh]
    L_0044aef6:
        mov al,byte ptr [esp+0D4h]
    L_0044aefd:
        shr dl,1
    L_0044aeff:
        and cl,87h
    L_0044af02:
        or dl,cl
    L_0044af04:
        or al,byte ptr [esp+54h]
    L_0044af08:
        mov cl,byte ptr [esp+4Fh]
    L_0044af0c:
        shr dl,1
    L_0044af0e:
        and al,83h
    L_0044af10:
        or dl,al
    L_0044af12:
        or cl,byte ptr [esp+0CFh]
    L_0044af19:
        mov al,byte ptr [esp+51h]
    L_0044af1d:
        shr dl,1
    L_0044af1f:
        and cl,81h
    L_0044af22:
        or dl,cl
    L_0044af24:
        or al,byte ptr [esp+0D1h]
    L_0044af2b:
        mov cl,byte ptr [esp+17h]
    L_0044af2f:
        shr dl,1
    L_0044af31:
        and al,80h
    L_0044af33:
        or dl,al
    L_0044af35:
        mov al,byte ptr [esp+24h]
    L_0044af39:
        movzx si,dl
    L_0044af3d:
        and cl,80h
    L_0044af40:
        and al,80h
    L_0044af42:
        movzx dx,cl
    L_0044af46:
        movzx cx,al
    L_0044af4a:
        mov al,byte ptr [esp+20h]
    L_0044af4e:
        and al,80h
    L_0044af50:
        shl edx,1
    L_0044af52:
        or edx,ecx
    L_0044af54:
        movzx cx,al
    L_0044af58:
        mov al,byte ptr [esp+1Dh]
    L_0044af5c:
        shl edx,1
    L_0044af5e:
        or edx,ecx
    L_0044af60:
        or al,byte ptr [esp+0CBh]
    L_0044af67:
        and al,80h
    L_0044af69:
        movzx cx,al
    L_0044af6d:
        mov al,byte ptr [esp+23h]
    L_0044af71:
        shl edx,1
    L_0044af73:
        and al,80h
    L_0044af75:
        or edx,ecx
    L_0044af77:
        movzx cx,al
    L_0044af7b:
        mov al,byte ptr [esp+14h]
    L_0044af7f:
        shl edx,1
    L_0044af81:
        and al,80h
    L_0044af83:
        or edx,ecx
    L_0044af85:
        movzx cx,al
    L_0044af89:
        mov al,byte ptr [esp+21h]
    L_0044af8d:
        shl edx,1
    L_0044af8f:
        and al,80h
    L_0044af91:
        or edx,ecx
    L_0044af93:
        movzx cx,al
    L_0044af97:
        shl edx,1
    L_0044af99:
        or edx,ecx
    L_0044af9b:
        shl edx,1
    L_0044af9d:
        or esi,edx
    L_0044af9f:
        mov dl,byte ptr [esp+4Dh]
    L_0044afa3:
        and dl,80h
    L_0044afa6:
        neg dl
    L_0044afa8:
        sbb edx,edx
    L_0044afaa:
        and edx,90h
    L_0044afb0:
        or esi,edx
    L_0044afb2:
        mov al,byte ptr [esp+53h]
    L_0044afb6:
        mov cl,byte ptr [esp+4Bh]
    L_0044afba:
        mov dl,byte ptr [esp+55h]
    L_0044afbe:
        and al,80h
    L_0044afc0:
        neg al
    L_0044afc2:
        sbb eax,eax
    L_0044afc4:
        and eax,60h
    L_0044afc7:
        and cl,80h
    L_0044afca:
        or esi,eax
    L_0044afcc:
        neg cl
    L_0044afce:
        sbb ecx,ecx
    L_0044afd0:
        and ecx,50h
    L_0044afd3:
        and dl,80h
    L_0044afd6:
        or esi,ecx
    L_0044afd8:
        neg dl
    L_0044afda:
        sbb edx,edx
    L_0044afdc:
        and edx,0A0h
    L_0044afe2:
        or esi,edx
    L_0044afe4:
        push 0
    L_0044afe6:
        push 0
    L_0044afe8:
        mov ecx,esi
    L_0044afea:
        call asm_FUN_0044a190_0044a190
    L_0044afef:
        mov ecx,dword ptr [esp+104h]
    L_0044aff6:
        pop esi
    L_0044aff7:
        xor ecx,esp
    L_0044aff9:
        call asm_security_check_cookie_00458ea5
    L_0044affe:
        add esp,104h
    L_0044b004:
        ret
    }
}
