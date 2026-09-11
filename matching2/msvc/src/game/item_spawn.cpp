#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BB00..0x0041BE18: FUN_0041bb00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bb00_0041bb00() {
    __asm {
    L_0041bb00:
        push ebx
    L_0041bb01:
        push ebp
    L_0041bb02:
        mov ebp,dword ptr [esp+0Ch]
    L_0041bb06:
        push esi
    L_0041bb07:
        xor ebx,ebx
    L_0041bb09:
        cmp ebp,8
    L_0041bb0c:
        push edi
    L_0041bb0d:
        mov esi,eax
    L_0041bb0f:
        je asm_target_0041bccd
    L_0041bb15:
        add esi,14h
    L_0041bb18:
        xor eax,eax
    L_0041bb1a:
        lea ebx,[ebx+force_disp32_zero]
    L_0041bb20:
        cmp dword ptr [esi+3DCh],ebx
    L_0041bb26:
        je short L_0041bb3f
    L_0041bb28:
        inc eax
    L_0041bb29:
        add esi,3F0h
    L_0041bb2f:
        cmp eax,96h
    L_0041bb34:
        jl short L_0041bb20
    L_0041bb36:
        pop edi
    L_0041bb37:
        pop esi
    L_0041bb38:
        pop ebp
    L_0041bb39:
        xor eax,eax
    L_0041bb3b:
        pop ebx
    L_0041bb3c:
        ret 10h
    L_0041bb3f:
        mov dword ptr [esi+3DCh],1
    L_0041bb49:
        mov edx,dword ptr [ecx]
    L_0041bb4b:
        lea edi,[esi+3ACh]
    L_0041bb51:
        mov eax,edi
    L_0041bb53:
        mov dword ptr [eax],edx
    L_0041bb55:
        mov edx,dword ptr [ecx+4]
    L_0041bb58:
        mov dword ptr [eax+4],edx
    L_0041bb5b:
        mov ecx,dword ptr [ecx+8]
    L_0041bb5e:
        mov dword ptr [eax+8],ecx
    L_0041bb61:
        fld dword ptr [edi]
    L_0041bb63:
        fcomp dword ptr [data_00470b40]
    L_0041bb69:
        fnstsw ax
    L_0041bb6b:
        test ah,41h
    L_0041bb6e:
        jp short L_0041bb78
    L_0041bb70:
        mov dword ptr [edi],0C3400000h
    L_0041bb76:
        jmp short L_0041bb8d
    L_0041bb78:
        fld dword ptr [edi]
    L_0041bb7a:
        fcomp dword ptr [data_00470b3c]
    L_0041bb80:
        fnstsw ax
    L_0041bb82:
        test ah,1
    L_0041bb85:
        jne short L_0041bb8d
    L_0041bb87:
        mov dword ptr [edi],43400000h
    L_0041bb8d:
        mov edx,dword ptr [esp+20h]
    L_0041bb91:
        mov eax,dword ptr [esp+1Ch]
    L_0041bb95:
        push edx
    L_0041bb96:
        push eax
    L_0041bb97:
        lea ecx,[esi+3B8h]
    L_0041bb9d:
        call asm_FUN_0041beb0_0041beb0
    L_0041bba2:
        mov dword ptr [esi+3C0h],ebx
    L_0041bba8:
        mov eax,dword ptr [esi+3D8h]
    L_0041bbae:
        test al,1
    L_0041bbb0:
        jne short L_0041bbdb
    L_0041bbb2:
        or eax,1
    L_0041bbb5:
        mov dword ptr [esi+3CCh],ebx
    L_0041bbbb:
        mov dword ptr [esi+3C8h],0FFF0BDC1h
    L_0041bbc5:
        mov dword ptr [esi+3D0h],ebx
    L_0041bbcb:
        mov dword ptr [esi+3D4h],476F78h
    L_0041bbd5:
        mov dword ptr [esi+3D8h],eax
    L_0041bbdb:
        mov dword ptr [esi+3CCh],ebx
    L_0041bbe1:
        mov dword ptr [esi+3D0h],ebx
    L_0041bbe7:
        mov dword ptr [esi+3C8h],0FFFFFFFFh
    L_0041bbf1:
        mov dword ptr [esi+3C4h],ebx
    L_0041bbf7:
        cmp word ptr [data_00474c48],64h
    L_0041bbff:
        jl short L_0041bc23
    L_0041bc01:
        lea eax,[ebp-1]
    L_0041bc04:
        cmp eax,0Ah
    L_0041bc07:
        ja short L_0041bc23
    L_0041bc09:
        movzx ecx,byte ptr [eax+41BE28h]
    L_0041bc10:
        jmp dword ptr [ecx*4+41BE1Ch]
    L_0041bc17:
        mov ebp,5
    L_0041bc1c:
        jmp short L_0041bc23
    L_0041bc1e:
        mov ebp,9
    L_0041bc23:
        cmp dword ptr [esi+3E0h],3
    L_0041bc2a:
        jne short L_0041bc47
    L_0041bc2c:
        mov eax,dword ptr [data_004776f0]
    L_0041bc31:
        mov ecx,dword ptr [eax+3E0B50h]
    L_0041bc37:
        push 189h
    L_0041bc3c:
        lea edx,[esp+24h]
    L_0041bc40:
        push edx
    L_0041bc41:
        push ecx
    L_0041bc42:
        call asm_PlayerAnimation_Create_00448db0
    L_0041bc47:
        cmp ebp,0Ah
    L_0041bc4a:
        mov dword ptr [esi+3E0h],ebp
    L_0041bc50:
        mov dword ptr [esi+3E4h],ebp
    L_0041bc56:
        jne short L_0041bc8c
    L_0041bc58:
        mov edx,dword ptr [data_004776f0]
    L_0041bc5e:
        mov dword ptr [esi+3E4h],1
    L_0041bc68:
        mov eax,dword ptr [edx+3E0B50h]
    L_0041bc6e:
        push eax
    L_0041bc6f:
        mov eax,177h
    L_0041bc74:
        call asm_FUN_00404f30_00404f30
    L_0041bc79:
        mov eax,dword ptr [esp+18h]
    L_0041bc7d:
        pop edi
    L_0041bc7e:
        mov dword ptr [esi+2FCh],eax
    L_0041bc84:
        pop esi
    L_0041bc85:
        pop ebp
    L_0041bc86:
        xor eax,eax
    L_0041bc88:
        pop ebx
    L_0041bc89:
        ret 10h
    L_0041bc8c:
        cmp ebp,0Bh
    L_0041bc8f:
        mov ecx,dword ptr [data_004776f0]
    L_0041bc95:
        jne short L_0041bca8
    L_0041bc97:
        mov dword ptr [esi+3E4h],4
    L_0041bca1:
        mov eax,17Ah
    L_0041bca6:
        jmp short L_0041bcae
    L_0041bca8:
        lea eax,[ebp+176h]
    L_0041bcae:
        mov edx,dword ptr [ecx+3E0B50h]
    L_0041bcb4:
        push edx
    L_0041bcb5:
        call asm_FUN_00404f30_00404f30
    L_0041bcba:
        mov eax,dword ptr [esp+18h]
    L_0041bcbe:
        pop edi
    L_0041bcbf:
        mov dword ptr [esi+2FCh],eax
    L_0041bcc5:
        pop esi
    L_0041bcc6:
        pop ebp
    L_0041bcc7:
        xor eax,eax
    L_0041bcc9:
        pop ebx
    L_0041bcca:
        ret 10h
    L_0041bccd:
        mov eax,dword ptr [esi+21CEB8h]
    L_0041bcd3:
        mov edi,dword ptr [esi+21CEBCh]
    L_0041bcd9:
        mov edx,eax
    L_0041bcdb:
        imul edx,3F0h
    L_0041bce1:
        inc edi
    L_0041bce2:
        lea edx,[edx+esi+24EB4h]
    L_0041bce9:
        mov dword ptr [esi+21CEBCh],edi
    L_0041bcef:
        cmp dword ptr [edx+3DCh],ebx
    L_0041bcf5:
        jne asm_target_0041bdf3
    L_0041bcfb:
        cmp edi,400h
    L_0041bd01:
        jl short L_0041bd14
    L_0041bd03:
        and eax,8000001Fh
    L_0041bd08:
        jns short L_0041bd0f
    L_0041bd0a:
        dec eax
    L_0041bd0b:
        or eax,0FFFFFFE0h
    L_0041bd0e:
        inc eax
    L_0041bd0f:
        add eax,10h
    L_0041bd12:
        jmp short L_0041bd52
    L_0041bd14:
        cmp edi,200h
    L_0041bd1a:
        jl short L_0041bd2d
    L_0041bd1c:
        and eax,8000000Fh
    L_0041bd21:
        jns short L_0041bd28
    L_0041bd23:
        dec eax
    L_0041bd24:
        or eax,0FFFFFFF0h
    L_0041bd27:
        inc eax
    L_0041bd28:
        add eax,8
    L_0041bd2b:
        jmp short L_0041bd52
    L_0041bd2d:
        cmp edi,100h
    L_0041bd33:
        jl short L_0041bd46
    L_0041bd35:
        and eax,80000007h
    L_0041bd3a:
        jns short L_0041bd41
    L_0041bd3c:
        dec eax
    L_0041bd3d:
        or eax,0FFFFFFF8h
    L_0041bd40:
        inc eax
    L_0041bd41:
        add eax,4
    L_0041bd44:
        jmp short L_0041bd52
    L_0041bd46:
        and eax,80000003h
    L_0041bd4b:
        jns short L_0041bd52
    L_0041bd4d:
        dec eax
    L_0041bd4e:
        or eax,0FFFFFFFCh
    L_0041bd51:
        inc eax
    L_0041bd52:
        mov dword ptr [edx+3ECh],eax
    L_0041bd58:
        mov eax,8
    L_0041bd5d:
        mov dword ptr [edx+3E0h],eax
    L_0041bd63:
        mov dword ptr [edx+3E4h],eax
    L_0041bd69:
        mov dword ptr [edx+3DCh],5
    L_0041bd73:
        mov edi,dword ptr [ecx]
    L_0041bd75:
        lea eax,[edx+3ACh]
    L_0041bd7b:
        mov dword ptr [eax],edi
    L_0041bd7d:
        mov edi,dword ptr [ecx+4]
    L_0041bd80:
        mov dword ptr [eax+4],edi
    L_0041bd83:
        mov ecx,dword ptr [ecx+8]
    L_0041bd86:
        mov dword ptr [eax+8],ecx
    L_0041bd89:
        mov eax,dword ptr [esp+20h]
    L_0041bd8d:
        mov ecx,dword ptr [esp+1Ch]
    L_0041bd91:
        push eax
    L_0041bd92:
        push ecx
    L_0041bd93:
        lea ecx,[edx+3B8h]
    L_0041bd99:
        call asm_FUN_0041beb0_0041beb0
    L_0041bd9e:
        mov dword ptr [edx+3C0h],ebx
    L_0041bda4:
        mov eax,dword ptr [edx+3D8h]
    L_0041bdaa:
        test al,1
    L_0041bdac:
        jne short L_0041bdd7
    L_0041bdae:
        or eax,1
    L_0041bdb1:
        mov dword ptr [edx+3CCh],ebx
    L_0041bdb7:
        mov dword ptr [edx+3C8h],0FFF0BDC1h
    L_0041bdc1:
        mov dword ptr [edx+3D0h],ebx
    L_0041bdc7:
        mov dword ptr [edx+3D4h],476F78h
    L_0041bdd1:
        mov dword ptr [edx+3D8h],eax
    L_0041bdd7:
        mov dword ptr [edx+3CCh],ebx
    L_0041bddd:
        mov dword ptr [edx+3D0h],ebx
    L_0041bde3:
        mov dword ptr [edx+3C8h],0FFFFFFFFh
    L_0041bded:
        mov dword ptr [edx+3C4h],ebx
    L_0041bdf3:
        mov edx,dword ptr [esi+21CEB8h]
    L_0041bdf9:
        inc edx
    L_0041bdfa:
        and edx,800007FFh
    L_0041be00:
        jns short L_0041be0a
    L_0041be02:
        dec edx
    L_0041be03:
        or edx,0FFFFF800h
    L_0041be09:
        inc edx
    L_0041be0a:
        pop edi
    L_0041be0b:
        mov dword ptr [esi+21CEB8h],edx
    L_0041be11:
        pop esi
    L_0041be12:
        pop ebp
    L_0041be13:
        xor eax,eax
    L_0041be15:
        pop ebx
    L_0041be16:
        ret 10h
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x1e
        _emit 0xbc
        _emit 0x41
        _emit 0x00
        _emit 0x17
        _emit 0xbc
        _emit 0x41
        _emit 0x00
        _emit 0x23
        _emit 0xbc
        _emit 0x41
        _emit 0x00
        _emit 0x00
        _emit 0x02
        _emit 0x02
        _emit 0x00
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x01
        _emit 0x01
    }
}
