#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040BA90..0x0040BD17: FUN_0040ba90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ba90_0040ba90() {
    __asm {
    L_0040ba90:
        push 0FFFFFFFFh
    L_0040ba92:
        push 4654CEh
    L_0040ba97:
        mov eax,dword ptr fs:[0]
    L_0040ba9d:
        push eax
    L_0040ba9e:
        mov dword ptr fs:[0],esp
    L_0040baa5:
        sub esp,0Ch
    L_0040baa8:
        push ebp
    L_0040baa9:
        mov ebp,dword ptr [esp+20h]
    L_0040baad:
        push esi
    L_0040baae:
        mov esi,dword ptr [ebp+14h]
    L_0040bab1:
        mov eax,0FFFFFFFEh
    L_0040bab6:
        and esi,eax
    L_0040bab8:
        mov dword ptr [ebp+14h],esi
    L_0040babb:
        and dword ptr [ebp+28h],eax
    L_0040babe:
        mov ecx,dword ptr [ebp+3Ch]
    L_0040bac1:
        xor edx,edx
    L_0040bac3:
        and ecx,eax
    L_0040bac5:
        mov dword ptr [ebp+3Ch],ecx
    L_0040bac8:
        push edi
    L_0040bac9:
        mov dword ptr [ebp+0D0h],4703E4h
    L_0040bad3:
        mov dword ptr [ebp+0D4h],edx
    L_0040bad9:
        mov dword ptr [ebp+0D8h],edx
    L_0040badf:
        mov dword ptr [ebp+0DCh],edx
    L_0040bae5:
        mov dword ptr [ebp+0E0h],edx
    L_0040baeb:
        xor eax,eax
    L_0040baed:
        mov dword ptr [esp+20h],edx
    L_0040baf1:
        mov esi,dword ptr [data_00491c10]
    L_0040baf7:
        mov ecx,3Bh
    L_0040bafc:
        mov edi,ebp
    L_0040bafe:
        rep stosd
    L_0040bb00:
        lea eax,[ebp+40h]
    L_0040bb03:
        mov dword ptr [esp+0Ch],edx
    L_0040bb07:
        mov dword ptr [esp+10h],eax
    L_0040bb0b:
        push ebx
    L_0040bb0c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040bb10:
        mov ecx,dword ptr [data_004776e0]
    L_0040bb16:
        mov edi,dword ptr [ecx+899Ch]
    L_0040bb1c:
        call asm_FUN_00449950_00449950
    L_0040bb21:
        mov edx,dword ptr [esp+10h]
    L_0040bb25:
        mov ebx,eax
    L_0040bb27:
        mov eax,dword ptr [ebx+35Ch]
    L_0040bb2d:
        add edx,42h
    L_0040bb30:
        push edx
    L_0040bb31:
        or eax,40000000h
    L_0040bb36:
        push ebx
    L_0040bb37:
        mov ecx,edi
    L_0040bb39:
        mov dword ptr [ebx+20h],0Fh
    L_0040bb40:
        mov dword ptr [ebx+35Ch],eax
    L_0040bb46:
        call asm_FUN_00449870_00449870
    L_0040bb4b:
        mov esi,dword ptr [data_00491c10]
    L_0040bb51:
        lea eax,[esp+18h]
    L_0040bb55:
        mov edx,esi
    L_0040bb57:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040bb5c:
        mov eax,dword ptr [esp+18h]
    L_0040bb60:
        mov edi,dword ptr [esp+14h]
    L_0040bb64:
        mov ecx,eax
    L_0040bb66:
        test ecx,ecx
    L_0040bb68:
        mov dword ptr [edi],eax
    L_0040bb6a:
        jne short L_0040bb70
    L_0040bb6c:
        xor eax,eax
    L_0040bb6e:
        jmp short L_0040bbac
    L_0040bb70:
        mov eax,dword ptr [esi+72DAD4h]
    L_0040bb76:
        test eax,eax
    L_0040bb78:
        je short L_0040bb8d
    L_0040bb7a:
        lea ebx,[ebx+force_disp32_zero]
    L_0040bb80:
        mov edx,dword ptr [eax]
    L_0040bb82:
        cmp dword ptr [edx],ecx
    L_0040bb84:
        je short L_0040bba6
    L_0040bb86:
        mov eax,dword ptr [eax+4]
    L_0040bb89:
        test eax,eax
    L_0040bb8b:
        jne short L_0040bb80
    L_0040bb8d:
        mov eax,dword ptr [esi+72DADCh]
    L_0040bb93:
        test eax,eax
    L_0040bb95:
        je short L_0040bb6c
    L_0040bb97:
        mov edx,dword ptr [eax]
    L_0040bb99:
        cmp dword ptr [edx],ecx
    L_0040bb9b:
        je short L_0040bba6
    L_0040bb9d:
        mov eax,dword ptr [eax+4]
    L_0040bba0:
        test eax,eax
    L_0040bba2:
        jne short L_0040bb97
    L_0040bba4:
        jmp short L_0040bbac
    L_0040bba6:
        mov eax,dword ptr [eax]
    L_0040bba8:
        test eax,eax
    L_0040bbaa:
        jne short L_0040bbb2
    L_0040bbac:
        mov dword ptr [edi],0
    L_0040bbb2:
        mov dl,10h
    L_0040bbb4:
        mov byte ptr [eax+3A0h],dl
    L_0040bbba:
        mov ecx,dword ptr [edi]
    L_0040bbbc:
        test ecx,ecx
    L_0040bbbe:
        jne short L_0040bbc4
    L_0040bbc0:
        xor eax,eax
    L_0040bbc2:
        jmp short L_0040bbfc
    L_0040bbc4:
        mov eax,dword ptr [esi+72DAD4h]
    L_0040bbca:
        test eax,eax
    L_0040bbcc:
        je short L_0040bbdd
    L_0040bbce:
        mov edi,edi
    L_0040bbd0:
        mov ebx,dword ptr [eax]
    L_0040bbd2:
        cmp dword ptr [ebx],ecx
    L_0040bbd4:
        je short L_0040bbf6
    L_0040bbd6:
        mov eax,dword ptr [eax+4]
    L_0040bbd9:
        test eax,eax
    L_0040bbdb:
        jne short L_0040bbd0
    L_0040bbdd:
        mov eax,dword ptr [esi+72DADCh]
    L_0040bbe3:
        test eax,eax
    L_0040bbe5:
        je short L_0040bbc0
    L_0040bbe7:
        mov ebx,dword ptr [eax]
    L_0040bbe9:
        cmp dword ptr [ebx],ecx
    L_0040bbeb:
        je short L_0040bbf6
    L_0040bbed:
        mov eax,dword ptr [eax+4]
    L_0040bbf0:
        test eax,eax
    L_0040bbf2:
        jne short L_0040bbe7
    L_0040bbf4:
        jmp short L_0040bbfc
    L_0040bbf6:
        mov eax,dword ptr [eax]
    L_0040bbf8:
        test eax,eax
    L_0040bbfa:
        jne short L_0040bc02
    L_0040bbfc:
        mov dword ptr [edi],0
    L_0040bc02:
        mov byte ptr [eax+3A1h],dl
    L_0040bc08:
        mov ecx,dword ptr [edi]
    L_0040bc0a:
        test ecx,ecx
    L_0040bc0c:
        jne short L_0040bc12
    L_0040bc0e:
        xor eax,eax
    L_0040bc10:
        jmp short L_0040bc4c
    L_0040bc12:
        mov eax,dword ptr [esi+72DAD4h]
    L_0040bc18:
        test eax,eax
    L_0040bc1a:
        je short L_0040bc2d
    L_0040bc1c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040bc20:
        mov edx,dword ptr [eax]
    L_0040bc22:
        cmp dword ptr [edx],ecx
    L_0040bc24:
        je short L_0040bc46
    L_0040bc26:
        mov eax,dword ptr [eax+4]
    L_0040bc29:
        test eax,eax
    L_0040bc2b:
        jne short L_0040bc20
    L_0040bc2d:
        mov eax,dword ptr [esi+72DADCh]
    L_0040bc33:
        test eax,eax
    L_0040bc35:
        je short L_0040bc0e
    L_0040bc37:
        mov edx,dword ptr [eax]
    L_0040bc39:
        cmp dword ptr [edx],ecx
    L_0040bc3b:
        je short L_0040bc46
    L_0040bc3d:
        mov eax,dword ptr [eax+4]
    L_0040bc40:
        test eax,eax
    L_0040bc42:
        jne short L_0040bc37
    L_0040bc44:
        jmp short L_0040bc4c
    L_0040bc46:
        mov eax,dword ptr [eax]
    L_0040bc48:
        test eax,eax
    L_0040bc4a:
        jne short L_0040bc52
    L_0040bc4c:
        mov dword ptr [edi],0
    L_0040bc52:
        or dword ptr [eax+360h],2
    L_0040bc59:
        mov eax,dword ptr [esp+10h]
    L_0040bc5d:
        inc eax
    L_0040bc5e:
        add edi,4
    L_0040bc61:
        cmp eax,5
    L_0040bc64:
        mov dword ptr [esp+10h],eax
    L_0040bc68:
        mov dword ptr [esp+14h],edi
    L_0040bc6c:
        jb asm_target_0040bb10
    L_0040bc72:
        mov eax,dword ptr [esp+30h]
    L_0040bc76:
        mov dword ptr [ebp+54h],eax
    L_0040bc79:
        mov ecx,dword ptr [ebp+14h]
    L_0040bc7c:
        xor eax,eax
    L_0040bc7e:
        test cl,1
    L_0040bc81:
        mov esi,0FFF0BDC1h
    L_0040bc86:
        mov edx,476F78h
    L_0040bc8b:
        pop ebx
    L_0040bc8c:
        jne short L_0040bca0
    L_0040bc8e:
        or ecx,1
    L_0040bc91:
        mov dword ptr [ebp+8],eax
    L_0040bc94:
        mov dword ptr [ebp+4],esi
    L_0040bc97:
        mov dword ptr [ebp+0Ch],eax
    L_0040bc9a:
        mov dword ptr [ebp+10h],edx
    L_0040bc9d:
        mov dword ptr [ebp+14h],ecx
    L_0040bca0:
        or edi,0FFFFFFFFh
    L_0040bca3:
        mov dword ptr [ebp+8],eax
    L_0040bca6:
        mov dword ptr [ebp+0Ch],eax
    L_0040bca9:
        mov dword ptr [ebp+4],edi
    L_0040bcac:
        mov ecx,dword ptr [ebp+28h]
    L_0040bcaf:
        test cl,1
    L_0040bcb2:
        jne short L_0040bcc6
    L_0040bcb4:
        or ecx,1
    L_0040bcb7:
        mov dword ptr [ebp+1Ch],eax
    L_0040bcba:
        mov dword ptr [ebp+18h],esi
    L_0040bcbd:
        mov dword ptr [ebp+20h],eax
    L_0040bcc0:
        mov dword ptr [ebp+24h],edx
    L_0040bcc3:
        mov dword ptr [ebp+28h],ecx
    L_0040bcc6:
        mov dword ptr [ebp+1Ch],eax
    L_0040bcc9:
        mov dword ptr [ebp+20h],eax
    L_0040bccc:
        mov dword ptr [ebp+18h],edi
    L_0040bccf:
        mov ecx,dword ptr [ebp+3Ch]
    L_0040bcd2:
        test cl,1
    L_0040bcd5:
        jne short L_0040bce9
    L_0040bcd7:
        or ecx,1
    L_0040bcda:
        mov dword ptr [ebp+30h],eax
    L_0040bcdd:
        mov dword ptr [ebp+2Ch],esi
    L_0040bce0:
        mov dword ptr [ebp+34h],eax
    L_0040bce3:
        mov dword ptr [ebp+38h],edx
    L_0040bce6:
        mov dword ptr [ebp+3Ch],ecx
    L_0040bce9:
        mov ecx,dword ptr [esp+18h]
    L_0040bced:
        mov dword ptr [ebp+30h],eax
    L_0040bcf0:
        mov dword ptr [ebp+34h],eax
    L_0040bcf3:
        mov dword ptr [ebp+2Ch],edi
    L_0040bcf6:
        mov eax,dword ptr [ebp+74h]
    L_0040bcf9:
        or eax,1
    L_0040bcfc:
        pop edi
    L_0040bcfd:
        mov dword ptr [ebp+74h],eax
    L_0040bd00:
        mov dword ptr [ebp+7Ch],0FFFFFFh
    L_0040bd07:
        pop esi
    L_0040bd08:
        mov eax,ebp
    L_0040bd0a:
        pop ebp
    L_0040bd0b:
        mov dword ptr fs:[0],ecx
    L_0040bd12:
        add esp,18h
    L_0040bd15:
        ret 8
    }
}
