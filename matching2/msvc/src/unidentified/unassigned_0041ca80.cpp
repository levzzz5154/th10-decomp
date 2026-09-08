#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041CA80..0x0041CF77: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ca80() {
    __asm {
    L_0041ca80:
        push ecx
    L_0041ca81:
        push ebp
    L_0041ca82:
        mov ebp,ecx
    L_0041ca84:
        cmp dword ptr [ebp+400h],12h
    L_0041ca8b:
        jge asm_target_0041cf72
    L_0041ca91:
        push ebx
    L_0041ca92:
        push esi
    L_0041ca93:
        push edi
    L_0041ca94:
        jmp short L_0041caa0
    L_0041ca96:
        lea esp,[esp+force_disp32_zero]
    L_0041ca9d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041caa0:
        mov ecx,dword ptr [ebp+400h]
    L_0041caa6:
        lea eax,[ecx+ecx*2+8Ah]
    L_0041caad:
        mov edx,dword ptr [ebp+eax*8+10h]
    L_0041cab1:
        lea esi,[ebp+eax*8]
    L_0041cab5:
        xor ebx,ebx
    L_0041cab7:
        cmp edx,ebx
    L_0041cab9:
        je asm_target_0041cf6f
    L_0041cabf:
        cmp dword ptr [esi+14h],ebx
    L_0041cac2:
        jne short L_0041cad0
    L_0041cac4:
        cmp dword ptr [ebp+404h],ebx
    L_0041caca:
        jne asm_target_0041cf6f
    L_0041cad0:
        cmp edx,80000000h
    L_0041cad6:
        jne short L_0041cae4
    L_0041cad8:
        inc ecx
    L_0041cad9:
        mov dword ptr [ebp+400h],ecx
    L_0041cadf:
        jmp asm_target_0041cf62
    L_0041cae4:
        mov eax,edx
    L_0041cae6:
        cmp eax,8000h
    L_0041caeb:
        ja asm_target_0041cdba
    L_0041caf1:
        je asm_target_0041cd57
    L_0041caf7:
        cmp eax,80h
    L_0041cafc:
        ja asm_target_0041cc51
    L_0041cb02:
        je asm_target_0041cc80
    L_0041cb08:
        dec eax
    L_0041cb09:
        cmp eax,3Fh
    L_0041cb0c:
        ja asm_target_0041cf50
    L_0041cb12:
        movzx ecx,byte ptr [eax+41CF8Ch]
    L_0041cb19:
        jmp dword ptr [ecx*4+41CF78h]
    L_0041cb20:
        mov ecx,dword ptr [ebp+404h]
    L_0041cb26:
        or ecx,1
    L_0041cb29:
        push ebx
    L_0041cb2a:
        lea eax,[ebp+58h]
    L_0041cb2d:
        mov dword ptr [ebp+404h],ecx
    L_0041cb33:
        call asm_Player_SetSchedulerValue_00405410
    L_0041cb38:
        mov eax,dword ptr [ebp+400h]
    L_0041cb3e:
        mov dword ptr [ebp+7Ch],ebx
    L_0041cb41:
        inc eax
    L_0041cb42:
        jmp asm_target_0041cf5c
    L_0041cb47:
        or dword ptr [ebp+404h],10h
    L_0041cb4e:
        mov edx,dword ptr [esi]
    L_0041cb50:
        mov dword ptr [ebp+0A0h],edx
    L_0041cb56:
        fld dword ptr [esi+4]
    L_0041cb59:
        fcomp dword ptr [data_00470b50]
    L_0041cb5f:
        fnstsw ax
    L_0041cb61:
        test ah,41h
    L_0041cb64:
        jp short L_0041cb6b
    L_0041cb66:
        fld dword ptr [ebp+3Ch]
    L_0041cb69:
        jmp short L_0041cb8e
    L_0041cb6b:
        fld dword ptr [esi+4]
    L_0041cb6e:
        fcomp dword ptr [data_00470ccc]
    L_0041cb74:
        fnstsw ax
    L_0041cb76:
        test ah,1
    L_0041cb79:
        jne short L_0041cb8b
    L_0041cb7b:
        mov ecx,dword ptr [data_00477834]
    L_0041cb81:
        lea eax,[ebp+24h]
    L_0041cb84:
        call asm_Entity_AngleFromPoint_00426660
    L_0041cb89:
        jmp short L_0041cb8e
    L_0041cb8b:
        fld dword ptr [esi+4]
    L_0041cb8e:
        push ebx
    L_0041cb8f:
        fstp dword ptr [ebp+0A4h]
    L_0041cb95:
        lea eax,[ebp+8Ch]
    L_0041cb9b:
        call asm_Player_SetSchedulerValue_00405410
    L_0041cba0:
        mov ecx,dword ptr [ebp+0A0h]
    L_0041cba6:
        mov edx,dword ptr [ebp+0A4h]
    L_0041cbac:
        mov eax,dword ptr [esi+8]
    L_0041cbaf:
        push ecx
    L_0041cbb0:
        push edx
    L_0041cbb1:
        lea ecx,[ebp+0A8h]
    L_0041cbb7:
        mov dword ptr [ebp+0B4h],eax
    L_0041cbbd:
        call asm_SetPolar_Vector2_0041f800
    L_0041cbc2:
        cmp dword ptr [ebp+400h],ebx
    L_0041cbc8:
        je asm_target_0041cf50
    L_0041cbce:
        mov edi,dword ptr [ebp+40Ch]
    L_0041cbd4:
        cmp edi,ebx
    L_0041cbd6:
        jl asm_target_0041cf50
    L_0041cbdc:
        push ebx
    L_0041cbdd:
        mov ecx,492590h
    L_0041cbe2:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0041cbe7:
        mov eax,dword ptr [ebp+400h]
    L_0041cbed:
        inc eax
    L_0041cbee:
        jmp asm_target_0041cf5c
    L_0041cbf3:
        or dword ptr [ebp+404h],20h
    L_0041cbfa:
        mov eax,dword ptr [esi]
    L_0041cbfc:
        mov dword ptr [ebp+0D4h],eax
    L_0041cc02:
        mov ecx,dword ptr [esi+4]
    L_0041cc05:
        push ebx
    L_0041cc06:
        lea eax,[ebp+0C0h]
    L_0041cc0c:
        mov dword ptr [ebp+0D8h],ecx
    L_0041cc12:
        call asm_Player_SetSchedulerValue_00405410
    L_0041cc17:
        cmp dword ptr [ebp+400h],ebx
    L_0041cc1d:
        mov edx,dword ptr [esi+8]
    L_0041cc20:
        mov dword ptr [ebp+0E8h],edx
    L_0041cc26:
        je asm_target_0041cf50
    L_0041cc2c:
        mov edi,dword ptr [ebp+40Ch]
    L_0041cc32:
        cmp edi,ebx
    L_0041cc34:
        jl asm_target_0041cf50
    L_0041cc3a:
        push ebx
    L_0041cc3b:
        mov ecx,492590h
    L_0041cc40:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0041cc45:
        mov eax,dword ptr [ebp+400h]
    L_0041cc4b:
        inc eax
    L_0041cc4c:
        jmp asm_target_0041cf5c
    L_0041cc51:
        cmp eax,800h
    L_0041cc56:
        ja asm_target_0041cd19
    L_0041cc5c:
        je asm_target_0041ce92
    L_0041cc62:
        cmp eax,100h
    L_0041cc67:
        je short L_0041cc80
    L_0041cc69:
        cmp eax,400h
    L_0041cc6e:
        je asm_target_0041ce92
    L_0041cc74:
        mov eax,dword ptr [ebp+400h]
    L_0041cc7a:
        inc eax
    L_0041cc7b:
        jmp asm_target_0041cf5c
    L_0041cc80:
        or dword ptr [ebp+404h],edx
    L_0041cc86:
        mov eax,dword ptr [esi]
    L_0041cc88:
        mov dword ptr [ebp+10Ch],eax
    L_0041cc8e:
        fld dword ptr [esi+4]
    L_0041cc91:
        fcomp dword ptr [data_00470cc8]
    L_0041cc97:
        fnstsw ax
    L_0041cc99:
        test ah,41h
    L_0041cc9c:
        jne short L_0041cca3
    L_0041cc9e:
        fld dword ptr [esi+4]
    L_0041cca1:
        jmp short L_0041cca6
    L_0041cca3:
        fld dword ptr [ebp+48h]
    L_0041cca6:
        fstp dword ptr [ebp+108h]
    L_0041ccac:
        mov eax,dword ptr [ebp+104h]
    L_0041ccb2:
        test al,1
    L_0041ccb4:
        jne short L_0041ccdf
    L_0041ccb6:
        or eax,1
    L_0041ccb9:
        mov dword ptr [ebp+0F8h],ebx
    L_0041ccbf:
        mov dword ptr [ebp+0F4h],0FFF0BDC1h
    L_0041ccc9:
        mov dword ptr [ebp+0FCh],ebx
    L_0041cccf:
        mov dword ptr [ebp+100h],476F78h
    L_0041ccd9:
        mov dword ptr [ebp+104h],eax
    L_0041ccdf:
        mov dword ptr [ebp+0F8h],ebx
    L_0041cce5:
        mov dword ptr [ebp+0FCh],ebx
    L_0041cceb:
        mov dword ptr [ebp+0F4h],0FFFFFFFFh
    L_0041ccf5:
        mov ecx,dword ptr [esi+8]
    L_0041ccf8:
        mov eax,dword ptr [ebp+400h]
    L_0041ccfe:
        mov dword ptr [ebp+11Ch],ecx
    L_0041cd04:
        mov edx,dword ptr [esi+0Ch]
    L_0041cd07:
        mov dword ptr [ebp+120h],edx
    L_0041cd0d:
        mov dword ptr [ebp+124h],ebx
    L_0041cd13:
        inc eax
    L_0041cd14:
        jmp asm_target_0041cf5c
    L_0041cd19:
        cmp eax,4000h
    L_0041cd1e:
        jne asm_target_0041cf50
    L_0041cd24:
        mov eax,dword ptr [esi+8]
    L_0041cd27:
        mov edx,dword ptr [esi+0Ch]
    L_0041cd2a:
        mov eax,dword ptr [eax*4+474170h]
    L_0041cd31:
        mov ecx,dword ptr [data_004776f0]
    L_0041cd37:
        add eax,edx
    L_0041cd39:
        mov edx,dword ptr [ecx+3E0B50h]
    L_0041cd3f:
        lea esi,[ebp+600h]
    L_0041cd45:
        push edx
    L_0041cd46:
        call asm_FUN_00404f30_00404f30
    L_0041cd4b:
        mov eax,dword ptr [ebp+400h]
    L_0041cd51:
        inc eax
    L_0041cd52:
        jmp asm_target_0041cf5c
    L_0041cd57:
        or dword ptr [ebp+404h],edx
    L_0041cd5d:
        mov eax,dword ptr [ebp+16Ch]
    L_0041cd63:
        test al,1
    L_0041cd65:
        mov esi,dword ptr [esi+8]
    L_0041cd68:
        mov dword ptr [esp+10h],esi
    L_0041cd6c:
        jne short L_0041cd97
    L_0041cd6e:
        or eax,1
    L_0041cd71:
        mov dword ptr [ebp+160h],ebx
    L_0041cd77:
        mov dword ptr [ebp+15Ch],0FFF0BDC1h
    L_0041cd81:
        mov dword ptr [ebp+164h],ebx
    L_0041cd87:
        mov dword ptr [ebp+168h],476F78h
    L_0041cd91:
        mov dword ptr [ebp+16Ch],eax
    L_0041cd97:
        fild dword ptr [esp+10h]
    L_0041cd9b:
        mov dword ptr [ebp+160h],esi
    L_0041cda1:
        dec esi
    L_0041cda2:
        mov dword ptr [ebp+15Ch],esi
    L_0041cda8:
        fstp dword ptr [ebp+164h]
    L_0041cdae:
        mov eax,dword ptr [ebp+400h]
    L_0041cdb4:
        inc eax
    L_0041cdb5:
        jmp asm_target_0041cf5c
    L_0041cdba:
        cmp eax,1000000h
    L_0041cdbf:
        ja asm_target_0041ce75
    L_0041cdc5:
        je asm_target_0041ce63
    L_0041cdcb:
        cmp eax,100000h
    L_0041cdd0:
        ja short L_0041ce37
    L_0041cdd2:
        je short L_0041ce16
    L_0041cdd4:
        cmp eax,10000h
    L_0041cdd9:
        je short L_0041ce03
    L_0041cddb:
        cmp eax,20000h
    L_0041cde0:
        jne asm_target_0041cf50
    L_0041cde6:
        mov eax,dword ptr [ebp+24h]
    L_0041cde9:
        mov ebx,dword ptr [esi+8]
    L_0041cdec:
        push eax
    L_0041cded:
        mov esi,492590h
    L_0041cdf2:
        call asm_FUN_0043dd10_0043dd10
    L_0041cdf7:
        mov eax,dword ptr [ebp+400h]
    L_0041cdfd:
        inc eax
    L_0041cdfe:
        jmp asm_target_0041cf5c
    L_0041ce03:
        mov eax,dword ptr [ebp+400h]
    L_0041ce09:
        mov dword ptr [ebp+0Ch],3
    L_0041ce10:
        inc eax
    L_0041ce11:
        jmp asm_target_0041cf5c
    L_0041ce16:
        or dword ptr [ebp+404h],edx
    L_0041ce1c:
        mov ecx,dword ptr [esi+8]
    L_0041ce1f:
        push ecx
    L_0041ce20:
        lea eax,[ebp+190h]
    L_0041ce26:
        call asm_Player_SetSchedulerValue_00405410
    L_0041ce2b:
        mov eax,dword ptr [ebp+400h]
    L_0041ce31:
        inc eax
    L_0041ce32:
        jmp asm_target_0041cf5c
    L_0041ce37:
        cmp eax,200000h
    L_0041ce3c:
        jne asm_target_0041cf50
    L_0041ce42:
        or dword ptr [ebp+404h],edx
    L_0041ce48:
        mov edx,dword ptr [esi+8]
    L_0041ce4b:
        push edx
    L_0041ce4c:
        lea eax,[ebp+190h]
    L_0041ce52:
        call asm_Player_SetSchedulerValue_00405410
    L_0041ce57:
        mov eax,dword ptr [ebp+400h]
    L_0041ce5d:
        inc eax
    L_0041ce5e:
        jmp asm_target_0041cf5c
    L_0041ce63:
        mov eax,dword ptr [esi+8]
    L_0041ce66:
        inc ecx
    L_0041ce67:
        mov dword ptr [ebp+54h],eax
    L_0041ce6a:
        mov dword ptr [ebp+400h],ecx
    L_0041ce70:
        jmp asm_target_0041cf62
    L_0041ce75:
        cmp eax,2000000h
    L_0041ce7a:
        je asm_target_0041cf59
    L_0041ce80:
        cmp eax,4000000h
    L_0041ce85:
        je short L_0041cee3
    L_0041ce87:
        cmp eax,8000000h
    L_0041ce8c:
        jne asm_target_0041cf50
    L_0041ce92:
        cmp dword ptr [esi+8],ebx
    L_0041ce95:
        jle asm_target_0041cf50
    L_0041ce9b:
        mov eax,dword ptr [ebp+404h]
    L_0041cea1:
        or eax,edx
    L_0041cea3:
        mov dword ptr [ebp+404h],eax
    L_0041cea9:
        fld dword ptr [esi]
    L_0041ceab:
        fcomp dword ptr [data_00470b04]
    L_0041ceb1:
        fnstsw ax
    L_0041ceb3:
        test ah,1
    L_0041ceb6:
        jne short L_0041cec2
    L_0041ceb8:
        mov ecx,dword ptr [esi]
    L_0041ceba:
        mov dword ptr [ebp+13Ch],ecx
    L_0041cec0:
        jmp short L_0041cecb
    L_0041cec2:
        mov edx,dword ptr [ebp+48h]
    L_0041cec5:
        mov dword ptr [ebp+13Ch],edx
    L_0041cecb:
        dec dword ptr [esi+8]
    L_0041cece:
        mov eax,dword ptr [ebp+400h]
    L_0041ced4:
        mov dword ptr [ebp+154h],ebx
    L_0041ceda:
        mov dword ptr [ebp+150h],ebx
    L_0041cee0:
        inc eax
    L_0041cee1:
        jmp short L_0041cf5c
    L_0041cee3:
        or dword ptr [ebp+404h],4000000h
    L_0041ceed:
        mov eax,dword ptr [esi]
    L_0041ceef:
        mov dword ptr [ebp+20Ch],eax
    L_0041cef5:
        mov ecx,dword ptr [esi+4]
    L_0041cef8:
        mov dword ptr [ebp+210h],ecx
    L_0041cefe:
        mov eax,dword ptr [ebp+208h]
    L_0041cf04:
        test al,1
    L_0041cf06:
        jne short L_0041cf31
    L_0041cf08:
        or eax,1
    L_0041cf0b:
        mov dword ptr [ebp+1FCh],ebx
    L_0041cf11:
        mov dword ptr [ebp+1F8h],0FFF0BDC1h
    L_0041cf1b:
        mov dword ptr [ebp+200h],ebx
    L_0041cf21:
        mov dword ptr [ebp+204h],476F78h
    L_0041cf2b:
        mov dword ptr [ebp+208h],eax
    L_0041cf31:
        mov dword ptr [ebp+1FCh],ebx
    L_0041cf37:
        mov dword ptr [ebp+200h],ebx
    L_0041cf3d:
        mov dword ptr [ebp+1F8h],0FFFFFFFFh
    L_0041cf47:
        mov edx,dword ptr [esi+8]
    L_0041cf4a:
        mov dword ptr [ebp+220h],edx
    L_0041cf50:
        mov eax,dword ptr [ebp+400h]
    L_0041cf56:
        inc eax
    L_0041cf57:
        jmp short L_0041cf5c
    L_0041cf59:
        mov eax,dword ptr [esi+8]
    L_0041cf5c:
        mov dword ptr [ebp+400h],eax
    L_0041cf62:
        cmp dword ptr [ebp+400h],12h
    L_0041cf69:
        jl asm_target_0041caa0
    L_0041cf6f:
        pop edi
    L_0041cf70:
        pop esi
    L_0041cf71:
        pop ebx
    L_0041cf72:
        pop ebp
    L_0041cf73:
        pop ecx
    L_0041cf74:
        ret
    L_0041cf75:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
