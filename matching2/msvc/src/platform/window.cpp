#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameMain_00438ad0() {
    __asm {
    L_00438ad0:
        sub esp,20h
    L_00438ad3:
        mov eax,dword ptr [esp+24h]
    L_00438ad7:
        push ebp
    L_00438ad8:
        push esi
    L_00438ad9:
        push edi
    L_00438ada:
        xor ebp,ebp
    L_00438adc:
        push 0A004h
    L_00438ae1:
        mov dword ptr [esp+10h],ebp
    L_00438ae5:
        mov dword ptr [data_004924f8],eax
    L_00438aea:
        call asm_operator_new_00452493
    L_00438aef:
        mov edx,eax
    L_00438af1:
        add esp,4
    L_00438af4:
        cmp edx,ebp
    L_00438af6:
        je short L_00438b0b
    L_00438af8:
        mov ecx,2801h
    L_00438afd:
        xor eax,eax
    L_00438aff:
        mov edi,edx
    L_00438b01:
        rep stosd
    L_00438b03:
        mov dword ptr [edx+0A000h],ebp
    L_00438b09:
        jmp short L_00438b0d
    L_00438b0b:
        xor edx,edx
    L_00438b0d:
        push ebx
    L_00438b0e:
        mov ebx,dword ptr [data_004660b8]
    L_00438b14:
        mov dword ptr [data_00491be0],edx
    L_00438b1a:
        mov esi,492274h
    L_00438b1f:
        mov edi,7
    L_00438b24:
        push esi
    L_00438b25:
        call ebx
    L_00438b27:
        add esi,18h
    L_00438b2a:
        dec edi
    L_00438b2b:
        jne short L_00438b24
    L_00438b2d:
        push 46F77Ch
    L_00438b32:
        mov ecx,474F70h
    L_00438b37:
        call asm_TextLog_Append_0044b810
    L_00438b3c:
        add esp,4
    L_00438b3f:
        call asm_FUN_00439ff0_00439ff0
    L_00438b44:
        cmp eax,0FFFFFFFFh
    L_00438b47:
        je asm_target_00438dd0
    L_00438b4d:
        mov esi,dword ptr [esp+34h]
    L_00438b51:
        mov dword ptr [data_00491c28],esi
    L_00438b57:
        call asm_SaveSystemSettingsRetail_004392e0
    L_00438b5c:
        push 491C28h
    L_00438b61:
        mov ebx,46F770h
    L_00438b66:
        call asm_FUN_00420870_00420870
    L_00438b6b:
        test eax,eax
    L_00438b6d:
        jne asm_target_00438dce
    L_00438b73:
        mov eax,dword ptr [data_00491d78]
    L_00438b78:
        test ah,1
    L_00438b7b:
        je short L_00438b9e
    L_00438b7d:
        push 0
    L_00438b7f:
        push 43A3A0h
    L_00438b84:
        push 0
    L_00438b86:
        push 0CBh
    L_00438b8b:
        push esi
    L_00438b8c:
        call dword ptr [data_00466264]
    L_00438b92:
        cmp eax,6
    L_00438b95:
        setne cl
    L_00438b98:
        mov byte ptr [data_00491d65],cl
    L_00438b9e:
        call asm_FUN_0043a1c0_0043a1c0
    L_00438ba3:
        xor ebp,ebp
    L_00438ba5:
        push 48h
    L_00438ba7:
        call asm_operator_new_00452493
    L_00438bac:
        add esp,4
    L_00438baf:
        cmp eax,ebp
    L_00438bb1:
        je short L_00438bba
    L_00438bb3:
        call asm_D3DResourceManager_Initialize_00449aa0
    L_00438bb8:
        jmp short L_00438bbc
    L_00438bba:
        xor eax,eax
    L_00438bbc:
        push 20h
    L_00438bbe:
        mov dword ptr [data_00491be4],eax
    L_00438bc3:
        call asm_Direct3DCreate9_00452176
    L_00438bc8:
        cmp eax,ebp
    L_00438bca:
        mov dword ptr [data_00491c2c],eax
    L_00438bcf:
        jne short L_00438be8
    L_00438bd1:
        push 46F6A0h
    L_00438bd6:
        mov edi,474F70h
    L_00438bdb:
        call asm_TextLog_AppendLine_0044b8e0
    L_00438be0:
        add esp,4
    L_00438be3:
        jmp asm_target_00438dd0
    L_00438be8:
        mov ebx,esi
    L_00438bea:
        call asm_FUN_00439730_00439730
    L_00438bef:
        test eax,eax
    L_00438bf1:
        jne asm_target_00438dce
    L_00438bf7:
        mov edx,dword ptr [data_004924f0]
    L_00438bfd:
        push 4977B0h
    L_00438c02:
        push eax
    L_00438c03:
        push 492590h
    L_00438c08:
        push 43CCF0h
    L_00438c0d:
        push eax
    L_00438c0e:
        mov ecx,14B4h
    L_00438c13:
        mov edi,492590h
    L_00438c18:
        rep stosd
    L_00438c1a:
        push eax
    L_00438c1b:
        mov dword ptr [data_004977b8],edx
    L_00438c21:
        call dword ptr [data_00466118]
    L_00438c27:
        mov dword ptr [data_004977a8],eax
    L_00438c2c:
        call asm_FUN_00439890_00439890
    L_00438c31:
        test eax,eax
    L_00438c33:
        jne asm_target_00438dce
    L_00438c39:
        call asm_FUN_0044a0c0_0044a0c0
    L_00438c3e:
        call asm_Input_NormalizeKeyboardState_0044b080
    L_00438c43:
        push 732460h
    L_00438c48:
        call asm_operator_new_00452493
    L_00438c4d:
        xor ebx,ebx
    L_00438c4f:
        add esp,4
    L_00438c52:
        cmp eax,ebx
    L_00438c54:
        je short L_00438c5e
    L_00438c56:
        push eax
    L_00438c57:
        call asm_GameStateInit_00445900
    L_00438c5c:
        jmp short L_00438c60
    L_00438c5e:
        xor eax,eax
    L_00438c60:
        mov dword ptr [data_00491c10],eax
    L_00438c65:
        cmp byte ptr [data_00491d65],bl
    L_00438c6b:
        jne short L_00438c82
    L_00438c6d:
        push ebx
    L_00438c6e:
        push ebx
    L_00438c6f:
        call asm_WINNLSEnableIME_0045232c
    L_00438c74:
        push ebx
    L_00438c75:
        call dword ptr [data_00466230]
    L_00438c7b:
        push ebx
    L_00438c7c:
        call dword ptr [data_00466224]
    L_00438c82:
        fld qword ptr [data_00470b70]
    L_00438c88:
        fstp qword ptr [data_00492540]
    L_00438c8e:
        call asm_FUN_00439540_00439540
    L_00438c93:
        mov eax,dword ptr [data_004924f0]
    L_00438c98:
        fst qword ptr [data_00492540]
    L_00438c9e:
        fst qword ptr [data_00492538]
    L_00438ca4:
        push eax
    L_00438ca5:
        fst qword ptr [data_00492528]
    L_00438cab:
        fstp qword ptr [data_00492530]
    L_00438cb1:
        call dword ptr [data_004661f0]
    L_00438cb7:
        call asm_FUN_00420470_00420470
    L_00438cbc:
        cmp eax,ebx
    L_00438cbe:
        mov dword ptr [esp+10h],eax
    L_00438cc2:
        je short L_00438cda
    L_00438cc4:
        cmp eax,0FFFFFFFFh
    L_00438cc7:
        je asm_target_00438d95
    L_00438ccd:
        mov dword ptr [esp+10h],2
    L_00438cd5:
        jmp asm_target_00438d95
    L_00438cda:
        cmp dword ptr [data_004924f4],ebx
    L_00438ce0:
        mov dword ptr [esp+10h],ebx
    L_00438ce4:
        mov byte ptr [data_00492504],0FCh
    L_00438ceb:
        jne asm_target_00438d95
    L_00438cf1:
        push 1
    L_00438cf3:
        push ebx
    L_00438cf4:
        push ebx
    L_00438cf5:
        push ebx
    L_00438cf6:
        lea ecx,[esp+24h]
    L_00438cfa:
        push ecx
    L_00438cfb:
        call dword ptr [data_0046623c]
    L_00438d01:
        test eax,eax
    L_00438d03:
        je short L_00438d1d
    L_00438d05:
        lea edx,[esp+14h]
    L_00438d09:
        push edx
    L_00438d0a:
        call dword ptr [data_0046622c]
    L_00438d10:
        lea eax,[esp+14h]
    L_00438d14:
        push eax
    L_00438d15:
        call dword ptr [data_00466254]
    L_00438d1b:
        jmp short L_00438d89
    L_00438d1d:
        mov eax,dword ptr [data_00491c30]
    L_00438d22:
        mov ecx,dword ptr [eax]
    L_00438d24:
        push eax
    L_00438d25:
        call dword ptr [ecx+0Ch]
    L_00438d28:
        cmp eax,ebx
    L_00438d2a:
        jne short L_00438d48
    L_00438d2c:
        push 4924F0h
    L_00438d31:
        call asm_FUN_00439390_00439390
    L_00438d36:
        cmp eax,ebx
    L_00438d38:
        mov dword ptr [esp+10h],eax
    L_00438d3c:
        jne short L_00438d95
    L_00438d3e:
        mov eax,dword ptr [data_00491ff4]
    L_00438d43:
        and eax,0FFFFFFEFh
    L_00438d46:
        jmp short L_00438d84
    L_00438d48:
        cmp eax,88760869h
    L_00438d4d:
        jne short L_00438d89
    L_00438d4f:
        mov eax,dword ptr [data_00491c10]
    L_00438d54:
        call asm_DestroyEntityList_00438a30
    L_00438d59:
        mov eax,dword ptr [data_00491c30]
    L_00438d5e:
        mov edx,dword ptr [eax]
    L_00438d60:
        push 491D0Ch
    L_00438d65:
        push eax
    L_00438d66:
        call dword ptr [edx+40h]
    L_00438d69:
        test eax,eax
    L_00438d6b:
        jne short L_00438d95
    L_00438d6d:
        call asm_FUN_00439d20_00439d20
    L_00438d72:
        mov eax,dword ptr [data_00491ff4]
    L_00438d77:
        mov dword ptr [data_00491fd4],3
    L_00438d81:
        or eax,10h
    L_00438d84:
        mov dword ptr [data_00491ff4],eax
    L_00438d89:
        cmp dword ptr [data_004924f4],ebx
    L_00438d8f:
        je asm_target_00438cf1
    L_00438d95:
        mov eax,491C28h
    L_00438d9a:
        call asm_FUN_00420270_00420270
    L_00438d9f:
        mov eax,dword ptr [data_00491be4]
    L_00438da4:
        cmp eax,ebx
    L_00438da6:
        mov esi,eax
    L_00438da8:
        je short L_00438db9
    L_00438daa:
        push eax
    L_00438dab:
        call asm_D3DResourceManager_Destroy_00438880
    L_00438db0:
        push esi
    L_00438db1:
        call asm_free_004524a1
    L_00438db6:
        add esp,4
    L_00438db9:
        mov dword ptr [data_00491be4],ebx
    L_00438dbf:
        nop
    L_00438dc0:
        push 492590h
    L_00438dc5:
        call asm_FUN_0043ddf0_0043ddf0
    L_00438dca:
        test eax,eax
    L_00438dcc:
        jne short L_00438dc0
    L_00438dce:
        xor ebp,ebp
    L_00438dd0:
        mov edi,2
    L_00438dd5:
        mov esi,492590h
    L_00438dda:
        mov dword ptr [data_004977b4],edi
    L_00438de0:
        call asm_Platform_StopSoundWorkersRetail_0043cc40
    L_00438de5:
        mov eax,esi
    L_00438de7:
        call asm_FUN_0043d120_0043d120
    L_00438dec:
        mov eax,dword ptr [data_00491c10]
    L_00438df1:
        cmp eax,ebp
    L_00438df3:
        mov esi,eax
    L_00438df5:
        je short L_00438e06
    L_00438df7:
        push eax
    L_00438df8:
        call asm_FUN_00446220_00446220
    L_00438dfd:
        push esi
    L_00438dfe:
        call asm_free_004524a1
    L_00438e03:
        add esp,4
    L_00438e06:
        mov eax,dword ptr [data_00491c30]
    L_00438e0b:
        cmp eax,ebp
    L_00438e0d:
        mov dword ptr [data_00491c10],ebp
    L_00438e13:
        je short L_00438e35
    L_00438e15:
        mov ecx,dword ptr [eax]
    L_00438e17:
        push 491D0Ch
    L_00438e1c:
        push eax
    L_00438e1d:
        call dword ptr [ecx+40h]
    L_00438e20:
        mov eax,dword ptr [data_00491c30]
    L_00438e25:
        cmp eax,ebp
    L_00438e27:
        je short L_00438e35
    L_00438e29:
        mov edx,dword ptr [eax]
    L_00438e2b:
        push eax
    L_00438e2c:
        call dword ptr [edx+8]
    L_00438e2f:
        mov dword ptr [data_00491c30],ebp
    L_00438e35:
        mov eax,dword ptr [data_00491c2c]
    L_00438e3a:
        cmp eax,ebp
    L_00438e3c:
        je short L_00438e4a
    L_00438e3e:
        mov ecx,dword ptr [eax]
    L_00438e40:
        push eax
    L_00438e41:
        call dword ptr [ecx+8]
    L_00438e44:
        mov dword ptr [data_00491c2c],ebp
    L_00438e4a:
        mov eax,dword ptr [data_004924f0]
    L_00438e4f:
        cmp eax,ebp
    L_00438e51:
        je short L_00438e7f
    L_00438e53:
        push ebp
    L_00438e54:
        push eax
    L_00438e55:
        call dword ptr [data_0046624c]
    L_00438e5b:
        mov edx,dword ptr [data_004924f0]
    L_00438e61:
        push ebp
    L_00438e62:
        push ebp
    L_00438e63:
        push ebp
    L_00438e64:
        push ebp
    L_00438e65:
        push ebp
    L_00438e66:
        push edx
    L_00438e67:
        call dword ptr [data_004661f4]
    L_00438e6d:
        mov eax,dword ptr [data_004924f0]
    L_00438e72:
        push eax
    L_00438e73:
        call dword ptr [data_00466220]
    L_00438e79:
        mov dword ptr [data_004924f0],ebp
    L_00438e7f:
        push 1
    L_00438e81:
        call dword ptr [data_00466230]
    L_00438e87:
        cmp dword ptr [esp+10h],edi
    L_00438e8b:
        jne short L_00438efa
    L_00438e8d:
        mov ecx,474F70h
    L_00438e92:
        push 46F6F0h
    L_00438e97:
        mov dword ptr [data_00476f70],ecx
    L_00438e9d:
        mov byte ptr [data_00474f70],0
    L_00438ea4:
        call asm_TextLog_Append_0044b810
    L_00438ea9:
        mov al,byte ptr [data_00491d65]
    L_00438eae:
        add esp,4
    L_00438eb1:
        test al,al
    L_00438eb3:
        jne short L_00438ebd
    L_00438eb5:
        push 1
    L_00438eb7:
        push ebp
    L_00438eb8:
        call asm_WINNLSEnableIME_0045232c
    L_00438ebd:
        mov edi,dword ptr [data_0046623c]
    L_00438ec3:
        mov esi,3Ch
    L_00438ec8:
        push 1
    L_00438eca:
        push ebp
    L_00438ecb:
        push ebp
    L_00438ecc:
        push ebp
    L_00438ecd:
        lea ecx,[esp+24h]
    L_00438ed1:
        push ecx
    L_00438ed2:
        call edi
    L_00438ed4:
        test eax,eax
    L_00438ed6:
        je short L_00438eee
    L_00438ed8:
        lea edx,[esp+14h]
    L_00438edc:
        push edx
    L_00438edd:
        call dword ptr [data_0046622c]
    L_00438ee3:
        lea eax,[esp+14h]
    L_00438ee7:
        push eax
    L_00438ee8:
        call dword ptr [data_00466254]
    L_00438eee:
        dec esi
    L_00438eef:
        jne short L_00438ec8
    L_00438ef1:
        mov esi,dword ptr [esp+34h]
    L_00438ef5:
        jmp asm_target_00438ba5
    L_00438efa:
        push 491D48h
    L_00438eff:
        push 46F770h
    L_00438f04:
        mov edi,34h
    L_00438f09:
        call asm_File_WriteWholeFile_0044b540
    L_00438f0e:
        mov edi,dword ptr [data_00491fe8]
    L_00438f14:
        cmp edi,ebp
    L_00438f16:
        pop ebx
    L_00438f17:
        je short L_00438f3d
    L_00438f19:
        call asm_FUN_0043ae20_0043ae20
    L_00438f1e:
        mov eax,dword ptr [data_00491fe8]
    L_00438f23:
        cmp eax,ebp
    L_00438f25:
        mov esi,eax
    L_00438f27:
        je short L_00438f37
    L_00438f29:
        call asm_FUN_0043a910_0043a910
    L_00438f2e:
        push esi
    L_00438f2f:
        call asm_free_004524a1
    L_00438f34:
        add esp,4
    L_00438f37:
        mov dword ptr [data_00491fe8],ebp
    L_00438f3d:
        cmp dword ptr [data_00476f70],474F70h
    L_00438f47:
        je short L_00438f9a
    L_00438f49:
        push 46F7CCh
    L_00438f4e:
        mov ecx,474F70h
    L_00438f53:
        call asm_TextLog_Append_0044b810
    L_00438f58:
        mov al,byte ptr [data_00476f74]
    L_00438f5d:
        add esp,4
    L_00438f60:
        test al,al
    L_00438f62:
        je short L_00438f77
    L_00438f64:
        push 10h
    L_00438f66:
        push 46F7C8h
    L_00438f6b:
        push 474F70h
    L_00438f70:
        push ebp
    L_00438f71:
        call dword ptr [data_00466234]
    L_00438f77:
        mov eax,474F70h
    L_00438f7c:
        lea edx,[eax+1]
    L_00438f7f:
        nop
    L_00438f80:
        mov cl,byte ptr [eax]
    L_00438f82:
        inc eax
    L_00438f83:
        test cl,cl
    L_00438f85:
        jne short L_00438f80
    L_00438f87:
        sub eax,edx
    L_00438f89:
        push 474F70h
    L_00438f8e:
        push 46F7BCh
    L_00438f93:
        mov edi,eax
    L_00438f95:
        call asm_File_WriteWholeFile_0044b540
    L_00438f9a:
        mov ebp,dword ptr [data_004660bc]
    L_00438fa0:
        mov esi,492274h
    L_00438fa5:
        mov edi,7
    L_00438faa:
        lea ebx,[ebx+force_disp32_zero]
    L_00438fb0:
        push esi
    L_00438fb1:
        call ebp
    L_00438fb3:
        add esi,18h
    L_00438fb6:
        dec edi
    L_00438fb7:
        jne short L_00438fb0
    L_00438fb9:
        mov ecx,dword ptr [data_0049251c]
    L_00438fbf:
        mov esi,dword ptr [data_00466258]
    L_00438fc5:
        push 2
    L_00438fc7:
        push 0
    L_00438fc9:
        push ecx
    L_00438fca:
        push 11h
    L_00438fcc:
        call esi
    L_00438fce:
        mov edx,dword ptr [data_00492520]
    L_00438fd4:
        push 2
    L_00438fd6:
        push 0
    L_00438fd8:
        push edx
    L_00438fd9:
        push 55h
    L_00438fdb:
        call esi
    L_00438fdd:
        mov eax,dword ptr [data_00492524]
    L_00438fe2:
        push 2
    L_00438fe4:
        push 0
    L_00438fe6:
        push eax
    L_00438fe7:
        push 56h
    L_00438fe9:
        call esi
    L_00438feb:
        push 1
    L_00438fed:
        push 0
    L_00438fef:
        call asm_WINNLSEnableIME_0045232c
    L_00438ff4:
        mov eax,dword ptr [data_00491be0]
    L_00438ff9:
        test eax,eax
    L_00438ffb:
        mov edi,eax
    L_00438ffd:
        TH10_REL8(0x74, 0x00438ffd, VA_asm_target_00439032)
    L_00438fff:
        mov ecx,dword ptr [eax+0A000h]
    L_00439005:
        test ecx,ecx
    L_00439007:
        TH10_REL8(0x74, 0x00439007, VA_asm_target_00439029)
    L_00439009:
        xor esi,esi
    L_0043900b:
        TH10_REL8(0xeb, 0x0043900b, VA_asm_GameMain_part_00439010)
    }
}

// 0x00439010..0x0043903C: GameMain
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameMain_part_00439010() {
    __asm {
    L_00439010:
        mov eax,dword ptr [edi+esi*4]
    L_00439013:
        test eax,eax
    L_00439015:
        je short L_00439020
    L_00439017:
        push eax
    L_00439018:
        call asm_free_00452422
    L_0043901d:
        add esp,4
    L_00439020:
        inc esi
    L_00439021:
        cmp esi,2800h
    L_00439027:
        jl short L_00439010
    L_00439029:
        push edi
    L_0043902a:
        call asm_free_004524a1
    L_0043902f:
        add esp,4
    L_00439032:
        pop edi
    L_00439033:
        pop esi
    L_00439034:
        xor eax,eax
    L_00439036:
        pop ebp
    L_00439037:
        add esp,20h
    L_0043903a:
        ret 10h
    }
}

// 0x004390E0..0x004391E8: FUN_004390e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004390e0_004390e0() {
    __asm {
    L_004390e0:
        push ebx
    L_004390e1:
        mov ebx,dword ptr [esp+10h]
    L_004390e5:
        push ebp
    L_004390e6:
        mov ebp,dword ptr [esp+0Ch]
    L_004390ea:
        push esi
    L_004390eb:
        mov esi,dword ptr [esp+1Ch]
    L_004390ef:
        push edi
    L_004390f0:
        mov edi,dword ptr [esp+18h]
    L_004390f4:
        cmp edi,20h
    L_004390f7:
        ja asm_target_004391a1
    L_004390fd:
        je short L_0043914b
    L_004390ff:
        cmp edi,10h
    L_00439102:
        je short L_00439135
    L_00439104:
        cmp edi,14h
    L_00439107:
        je short L_0043913f
    L_00439109:
        cmp edi,1Ch
    L_0043910c:
        jne asm_target_004391d8
    L_00439112:
        xor eax,eax
    L_00439114:
        test ebx,ebx
    L_00439116:
        push esi
    L_00439117:
        sete al
    L_0043911a:
        push ebx
    L_0043911b:
        push edi
    L_0043911c:
        push ebp
    L_0043911d:
        mov dword ptr [data_004924fc],ebx
    L_00439123:
        mov dword ptr [data_00492500],eax
    L_00439128:
        call dword ptr [data_00466248]
    L_0043912e:
        pop edi
    L_0043912f:
        pop esi
    L_00439130:
        pop ebp
    L_00439131:
        pop ebx
    L_00439132:
        ret 10h
    L_00439135:
        or dword ptr [data_00491ff4],80h
    L_0043913f:
        pop edi
    L_00439140:
        pop esi
    L_00439141:
        pop ebp
    L_00439142:
        mov eax,1
    L_00439147:
        pop ebx
    L_00439148:
        ret 10h
    L_0043914b:
        mov al,byte ptr [data_00491d65]
    L_00439150:
        test al,al
    L_00439152:
        jne short L_00439179
    L_00439154:
        mov eax,dword ptr [data_00492500]
    L_00439159:
        test eax,eax
    L_0043915b:
        jne short L_00439179
    L_0043915d:
        push 0
    L_0043915f:
        call dword ptr [data_00466230]
    L_00439165:
        push 0
    L_00439167:
        call dword ptr [data_00466224]
    L_0043916d:
        pop edi
    L_0043916e:
        pop esi
    L_0043916f:
        pop ebp
    L_00439170:
        mov eax,1
    L_00439175:
        pop ebx
    L_00439176:
        ret 10h
    L_00439179:
        push 7F00h
    L_0043917e:
        push 0
    L_00439180:
        call dword ptr [data_00466260]
    L_00439186:
        push eax
    L_00439187:
        call dword ptr [data_00466224]
    L_0043918d:
        push 1
    L_0043918f:
        call dword ptr [data_00466230]
    L_00439195:
        pop edi
    L_00439196:
        pop esi
    L_00439197:
        pop ebp
    L_00439198:
        mov eax,1
    L_0043919d:
        pop ebx
    L_0043919e:
        ret 10h
    L_004391a1:
        cmp edi,201h
    L_004391a7:
        je short L_004391d1
    L_004391a9:
        cmp edi,3C9h
    L_004391af:
        jne short L_004391d8
    L_004391b1:
        mov edx,dword ptr [data_00491fe8]
    L_004391b7:
        test edx,edx
    L_004391b9:
        je short L_004391d8
    L_004391bb:
        call asm_FUN_0043aeb0_0043aeb0
    L_004391c0:
        push esi
    L_004391c1:
        push ebx
    L_004391c2:
        push edi
    L_004391c3:
        push ebp
    L_004391c4:
        call dword ptr [data_00466248]
    L_004391ca:
        pop edi
    L_004391cb:
        pop esi
    L_004391cc:
        pop ebp
    L_004391cd:
        pop ebx
    L_004391ce:
        ret 10h
    L_004391d1:
        push ebp
    L_004391d2:
        call dword ptr [data_004661f0]
    L_004391d8:
        push esi
    L_004391d9:
        push ebx
    L_004391da:
        push edi
    L_004391db:
        push ebp
    L_004391dc:
        call dword ptr [data_00466248]
    L_004391e2:
        pop edi
    L_004391e3:
        pop esi
    L_004391e4:
        pop ebp
    L_004391e5:
        pop ebx
    L_004391e6:
        ret 10h
    }
}

// 0x004392E0..0x00439343: SaveSystemSettingsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SaveSystemSettingsRetail_004392e0() {
    __asm {
    L_004392e0:
        push esi
    L_004392e1:
        mov esi,dword ptr [data_00466258]
    L_004392e7:
        push 0
    L_004392e9:
        push 49251Ch
    L_004392ee:
        push 0
    L_004392f0:
        push 10h
    L_004392f2:
        call esi
    L_004392f4:
        push 0
    L_004392f6:
        push 492520h
    L_004392fb:
        push 0
    L_004392fd:
        push 53h
    L_004392ff:
        call esi
    L_00439301:
        push 0
    L_00439303:
        push 492524h
    L_00439308:
        push 0
    L_0043930a:
        push 54h
    L_0043930c:
        call esi
    L_0043930e:
        push 2
    L_00439310:
        push 0
    L_00439312:
        push 0
    L_00439314:
        push 11h
    L_00439316:
        call esi
    L_00439318:
        push 2
    L_0043931a:
        push 0
    L_0043931c:
        push 0
    L_0043931e:
        push 55h
    L_00439320:
        call esi
    L_00439322:
        push 2
    L_00439324:
        push 0
    L_00439326:
        push 0
    L_00439328:
        push 56h
    L_0043932a:
        call esi
    L_0043932c:
        push 492508h
    L_00439331:
        call dword ptr [data_00466114]
    L_00439337:
        push 492510h
    L_0043933c:
        call dword ptr [data_004660fc]
    L_00439342:
        pop esi
    L_00439343:
        ret
    }
}

// 0x00439390..0x004393C8: FUN_00439390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439390_00439390() {
    __asm {
    L_00439390:
        push ebp
    L_00439391:
        mov ebp,dword ptr [esp+8]
    L_00439395:
        push esi
    L_00439396:
        push edi
    L_00439397:
        call asm_FUN_00439540_00439540
    L_0043939c:
        fcom qword ptr [ebp+40h]
    L_0043939f:
        fst qword ptr [ebp+38h]
    L_004393a2:
        fnstsw ax
    L_004393a4:
        test ah,5
    L_004393a7:
        jp short L_004393ac
    L_004393a9:
        fst qword ptr [ebp+48h]
    L_004393ac:
        fcom qword ptr [ebp+48h]
    L_004393af:
        fst qword ptr [ebp+40h]
    L_004393b2:
        fnstsw ax
    L_004393b4:
        test ah,41h
    L_004393b7:
        jne asm_target_00439527
    L_004393bd:
        fcomp qword ptr [ebp+48h]
    L_004393c0:
        fnstsw ax
    L_004393c2:
        test ah,41h
    L_004393c5:
        TH10_REL8(0x75, 0x004393c5, VA_asm_target_004393e9)
    L_004393c7:
        TH10_REL8(0xeb, 0x004393c7, VA_asm_FUN_00439390_part_004393d0)
    }
}

// 0x004393D0..0x00439538: FUN_00439390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439390_part_004393d0() {
    __asm {
    L_004393d0:
        fld qword ptr [ebp+48h]
    L_004393d3:
        fadd qword ptr [data_00470c90]
    L_004393d9:
        fstp qword ptr [ebp+48h]
    L_004393dc:
        fld qword ptr [ebp+48h]
    L_004393df:
        fcomp qword ptr [ebp+38h]
    L_004393e2:
        fnstsw ax
    L_004393e4:
        test ah,5
    L_004393e7:
        jnp short L_004393d0
    L_004393e9:
        mov esi,dword ptr [data_00491c10]
    L_004393ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004393f4:
        mov edi,491E94h
    L_004393f9:
        mov dword ptr [data_00491fac],edi
    L_004393ff:
        call asm_Camera_ApplyRetail_00421480
    L_00439404:
        mov edx,dword ptr [data_00491fac]
    L_0043940a:
        mov eax,dword ptr [data_00491c30]
    L_0043940f:
        mov ecx,dword ptr [eax]
    L_00439411:
        add edx,0CCh
    L_00439417:
        push edx
    L_00439418:
        push eax
    L_00439419:
        call dword ptr [ecx+0BCh]
    L_0043941f:
        mov eax,dword ptr [data_00491be4]
    L_00439424:
        push eax
    L_00439425:
        mov dword ptr [data_00491fb0],1
    L_0043942f:
        call asm_FUN_00449c00_00449c00
    L_00439434:
        push 492590h
    L_00439439:
        mov esi,eax
    L_0043943b:
        call asm_FUN_0043ddf0_0043ddf0
    L_00439440:
        test esi,esi
    L_00439442:
        jne short L_00439459
    L_00439444:
        mov esi,492254h
    L_00439449:
        call asm_Platform_StopWorker_0044c150
    L_0043944e:
        pop edi
    L_0043944f:
        pop esi
    L_00439450:
        mov eax,1
    L_00439455:
        pop ebp
    L_00439456:
        ret 4
    L_00439459:
        cmp esi,0FFFFFFFFh
    L_0043945c:
        jne short L_00439473
    L_0043945e:
        mov esi,492254h
    L_00439463:
        call asm_Platform_StopWorker_0044c150
    L_00439468:
        pop edi
    L_00439469:
        pop esi
    L_0043946a:
        mov eax,2
    L_0043946f:
        pop ebp
    L_00439470:
        ret 4
    L_00439473:
        mov al,byte ptr [ebp+14h]
    L_00439476:
        inc al
    L_00439478:
        mov byte ptr [ebp+14h],al
    L_0043947b:
        movzx ecx,byte ptr [data_00491d66]
    L_00439482:
        movsx edx,al
    L_00439485:
        inc ecx
    L_00439486:
        cmp ecx,edx
    L_00439488:
        jg asm_target_00439511
    L_0043948e:
        mov eax,dword ptr [data_00491c30]
    L_00439493:
        mov ecx,dword ptr [eax]
    L_00439495:
        push eax
    L_00439496:
        call dword ptr [ecx+0A4h]
    L_0043949c:
        mov eax,dword ptr [data_00491c10]
    L_004394a1:
        lea ecx,[eax+3ADACCh]
    L_004394a7:
        mov dword ptr [eax+3ADAC8h],0
    L_004394b1:
        mov dword ptr [eax+72DACCh],ecx
    L_004394b7:
        mov dword ptr [eax+72DAD0h],ecx
    L_004394bd:
        mov edi,491C28h
    L_004394c2:
        mov dword ptr [data_00492378],0FFh
    L_004394cc:
        call asm_FUN_00420cd0_00420cd0
    L_004394d1:
        mov edx,dword ptr [data_00491be4]
    L_004394d7:
        push edx
    L_004394d8:
        call asm_FUN_00449d40_00449d40
    L_004394dd:
        mov esi,dword ptr [data_00491c10]
    L_004394e3:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004394e8:
        mov eax,dword ptr [data_00491c30]
    L_004394ed:
        mov ecx,dword ptr [eax]
    L_004394ef:
        push 0
    L_004394f1:
        push 0
    L_004394f3:
        push eax
    L_004394f4:
        call dword ptr [ecx+104h]
    L_004394fa:
        mov eax,dword ptr [data_00491c30]
    L_004394ff:
        mov edx,dword ptr [eax]
    L_00439501:
        push eax
    L_00439502:
        call dword ptr [edx+0A8h]
    L_00439508:
        mov byte ptr [ebp+14h],0
    L_0043950c:
        call asm_FUN_004391f0_004391f0
    L_00439511:
        call asm_FUN_00439540_00439540
    L_00439516:
        fsub qword ptr [ebp+38h]
    L_00439519:
        pop edi
    L_0043951a:
        pop esi
    L_0043951b:
        fstp qword ptr [data_004923a0]
    L_00439521:
        xor eax,eax
    L_00439523:
        pop ebp
    L_00439524:
        ret 4
    L_00439527:
        push 0
    L_00439529:
        fstp st(0)
    L_0043952b:
        call dword ptr [data_004660ac]
    L_00439531:
        pop edi
    L_00439532:
        pop esi
    L_00439533:
        xor eax,eax
    L_00439535:
        pop ebp
    L_00439536:
        ret 4
    }
}

// 0x00439730..0x00439884: FUN_00439730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439730_00439730() {
    __asm {
    L_00439730:
        sub esp,28h
    L_00439733:
        xor eax,eax
    L_00439735:
        mov dword ptr [esp],eax
    L_00439738:
        mov dword ptr [esp+4],eax
    L_0043973c:
        mov dword ptr [esp+8],eax
    L_00439740:
        mov dword ptr [esp+0Ch],eax
    L_00439744:
        mov dword ptr [esp+10h],eax
    L_00439748:
        mov dword ptr [esp+14h],eax
    L_0043974c:
        mov dword ptr [esp+18h],eax
    L_00439750:
        mov dword ptr [esp+1Ch],eax
    L_00439754:
        push esi
    L_00439755:
        mov dword ptr [esp+24h],eax
    L_00439759:
        push 4
    L_0043975b:
        mov dword ptr [esp+2Ch],eax
    L_0043975f:
        call dword ptr [data_00466010]
    L_00439765:
        push 7F00h
    L_0043976a:
        push 0
    L_0043976c:
        mov dword ptr [esp+28h],eax
    L_00439770:
        call dword ptr [data_00466260]
    L_00439776:
        lea ecx,[esp+4]
    L_0043977a:
        push ecx
    L_0043977b:
        mov dword ptr [esp+20h],eax
    L_0043977f:
        mov dword ptr [esp+18h],ebx
    L_00439783:
        mov dword ptr [esp+0Ch],4390E0h
    L_0043978b:
        mov dword ptr [data_004924fc],1
    L_00439795:
        mov dword ptr [data_00492500],0
    L_0043979f:
        mov dword ptr [esp+2Ch],46F698h
    L_004397a7:
        call dword ptr [data_004661f8]
    L_004397ad:
        mov al,byte ptr [data_00491d65]
    L_004397b2:
        test al,al
    L_004397b4:
        jne short L_004397e4
    L_004397b6:
        push 0
    L_004397b8:
        push ebx
    L_004397b9:
        push 0
    L_004397bb:
        push 0
    L_004397bd:
        push 1E0h
    L_004397c2:
        push 280h
    L_004397c7:
        push 0
    L_004397c9:
        push 0
    L_004397cb:
        push 0CF0000h
    L_004397d0:
        push 46F66Ch
    L_004397d5:
        push 46F698h
    L_004397da:
        push 0
    L_004397dc:
        call dword ptr [data_00466238]
    L_004397e2:
        jmp short L_00439834
    L_004397e4:
        mov esi,dword ptr [data_0046625c]
    L_004397ea:
        push ebp
    L_004397eb:
        push edi
    L_004397ec:
        push 7
    L_004397ee:
        call esi
    L_004397f0:
        push 8
    L_004397f2:
        lea edi,[eax+eax+280h]
    L_004397f9:
        call esi
    L_004397fb:
        push 4
    L_004397fd:
        mov ebp,eax
    L_004397ff:
        call esi
    L_00439801:
        push 0
    L_00439803:
        push ebx
    L_00439804:
        push 0
    L_00439806:
        push 0
    L_00439808:
        lea eax,[eax+ebp*2+1E0h]
    L_0043980f:
        push eax
    L_00439810:
        push edi
    L_00439811:
        push 80000000h
    L_00439816:
        push 80000000h
    L_0043981b:
        push 100A0000h
    L_00439820:
        push 46F66Ch
    L_00439825:
        push 46F698h
    L_0043982a:
        push 0
    L_0043982c:
        call dword ptr [data_00466238]
    L_00439832:
        pop edi
    L_00439833:
        pop ebp
    L_00439834:
        test eax,eax
    L_00439836:
        mov dword ptr [data_004924f0],eax
    L_0043983b:
        mov dword ptr [data_00491c70],eax
    L_00439840:
        jne short L_0043984c
    L_00439842:
        mov eax,1
    L_00439847:
        pop esi
    L_00439848:
        add esp,28h
    L_0043984b:
        ret
    L_0043984c:
        mov esi,dword ptr [data_00466228]
    L_00439852:
        push 0
    L_00439854:
        push 0F020h
    L_00439859:
        push 112h
    L_0043985e:
        push eax
    L_0043985f:
        call esi
    L_00439861:
        push 10h
    L_00439863:
        call dword ptr [data_004660ac]
    L_00439869:
        mov edx,dword ptr [data_004924f0]
    L_0043986f:
        push 0
    L_00439871:
        push 0F120h
    L_00439876:
        push 112h
    L_0043987b:
        push edx
    L_0043987c:
        call esi
    L_0043987e:
        xor eax,eax
    L_00439880:
        pop esi
    L_00439881:
        add esp,28h
    L_00439884:
        ret
    }
}

// 0x00439FF0..0x0043A11C: FUN_00439ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439ff0_00439ff0() {
    __asm {
    L_00439ff0:
        sub esp,258h
    L_00439ff6:
        mov eax,dword ptr [data_00473660]
    L_00439ffb:
        xor eax,esp
    L_00439ffd:
        push edi
    L_00439ffe:
        push 46F3ACh
    L_0043a003:
        push 1
    L_0043a005:
        push 0
    L_0043a007:
        mov dword ptr [esp+264h],eax
    L_0043a00e:
        call dword ptr [data_00466110]
    L_0043a014:
        mov dword ptr [data_00497ba8],eax
    L_0043a019:
        call dword ptr [data_0046610c]
    L_0043a01f:
        cmp eax,0B7h
    L_0043a024:
        jne short L_0043a051
    L_0043a026:
        push 46F394h
    L_0043a02b:
        mov edi,474F70h
    L_0043a030:
        call asm_TextLog_AppendLine_0044b8e0
    L_0043a035:
        add esp,4
    L_0043a038:
        or eax,0FFFFFFFFh
    L_0043a03b:
        pop edi
    L_0043a03c:
        mov ecx,dword ptr [esp+254h]
    L_0043a043:
        xor ecx,esp
    L_0043a045:
        call asm_security_check_cookie_00458ea5
    L_0043a04a:
        add esp,258h
    L_0043a050:
        ret
    L_0043a051:
        xor eax,eax
    L_0043a053:
        mov dword ptr [esp+4],44h
    L_0043a05b:
        mov ecx,10h
    L_0043a060:
        lea edi,[esp+8]
    L_0043a064:
        rep stosd
    L_0043a066:
        push 105h
    L_0043a06b:
        lea eax,[esp+154h]
    L_0043a072:
        push eax
    L_0043a073:
        push 0
    L_0043a075:
        call dword ptr [data_004660dc]
    L_0043a07b:
        push 105h
    L_0043a080:
        lea ecx,[esp+4Ch]
    L_0043a084:
        push ecx
    L_0043a085:
        call dword ptr [data_00466100]
    L_0043a08b:
        lea edx,[esp+4]
    L_0043a08f:
        push edx
    L_0043a090:
        call dword ptr [data_00466108]
    L_0043a096:
        mov eax,dword ptr [esp+10h]
    L_0043a09a:
        test eax,eax
    L_0043a09c:
        je asm_target_0043a179
    L_0043a0a2:
        push esi
    L_0043a0a3:
        push 2Eh
    L_0043a0a5:
        push eax
    L_0043a0a6:
        call asm_strrchr_00452930
    L_0043a0ab:
        mov esi,eax
    L_0043a0ad:
        mov eax,dword ptr [esp+1Ch]
    L_0043a0b1:
        add esp,8
    L_0043a0b4:
        push eax
    L_0043a0b5:
        call asm_File_ProbeExists_0044b4d0
    L_0043a0ba:
        test eax,eax
    L_0043a0bc:
        je asm_target_0043a16e
    L_0043a0c2:
        test esi,esi
    L_0043a0c4:
        je asm_target_0043a16e
    L_0043a0ca:
        push ebx
    L_0043a0cb:
        push 46F38Ch
    L_0043a0d0:
        push esi
    L_0043a0d1:
        call asm_stricmp_0046054e
    L_0043a0d6:
        add esp,8
    L_0043a0d9:
        test eax,eax
    L_0043a0db:
        jne short L_0043a111
    L_0043a0dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0043a0e0:
        mov ecx,dword ptr [esp+18h]
    L_0043a0e4:
        push ecx
    L_0043a0e5:
        mov edi,104h
    L_0043a0ea:
        lea ebx,[esp+54h]
    L_0043a0ee:
        call asm_FUN_0043a290_0043a290
    L_0043a0f3:
        mov edx,ebx
    L_0043a0f5:
        push 2Eh
    L_0043a0f7:
        push edx
    L_0043a0f8:
        call asm_strrchr_00452930
    L_0043a0fd:
        push 46F38Ch
    L_0043a102:
        push eax
    L_0043a103:
        call asm_stricmp_0046054e
    L_0043a108:
        add esp,10h
    L_0043a10b:
        test eax,eax
    L_0043a10d:
        je short L_0043a0e0
    L_0043a10f:
        TH10_REL8(0xeb, 0x0043a10f, VA_asm_target_0043a12a)
    L_0043a111:
        mov eax,dword ptr [esp+18h]
    L_0043a115:
        lea edx,[esp+50h]
    L_0043a119:
        sub edx,eax
    L_0043a11b:
        TH10_REL8(0xeb, 0x0043a11b, VA_asm_FUN_00439ff0_part_0043a120)
    }
}

// 0x0043A120..0x0043A1A9: FUN_00439ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439ff0_part_0043a120() {
    __asm {
    L_0043a120:
        mov cl,byte ptr [eax]
    L_0043a122:
        mov byte ptr [edx+eax],cl
    L_0043a125:
        inc eax
    L_0043a126:
        test cl,cl
    L_0043a128:
        jne short L_0043a120
    L_0043a12a:
        lea esi,[esp+50h]
    L_0043a12e:
        lea eax,[esp+158h]
    L_0043a135:
        mov dl,byte ptr [eax]
    L_0043a137:
        mov bl,byte ptr [esi]
    L_0043a139:
        mov cl,dl
    L_0043a13b:
        cmp dl,bl
    L_0043a13d:
        jne short L_0043a15d
    L_0043a13f:
        test cl,cl
    L_0043a141:
        je short L_0043a159
    L_0043a143:
        mov dl,byte ptr [eax+1]
    L_0043a146:
        mov bl,byte ptr [esi+1]
    L_0043a149:
        mov cl,dl
    L_0043a14b:
        cmp dl,bl
    L_0043a14d:
        jne short L_0043a15d
    L_0043a14f:
        add eax,2
    L_0043a152:
        add esi,2
    L_0043a155:
        test cl,cl
    L_0043a157:
        jne short L_0043a135
    L_0043a159:
        xor eax,eax
    L_0043a15b:
        jmp short L_0043a162
    L_0043a15d:
        sbb eax,eax
    L_0043a15f:
        sbb eax,0FFFFFFFFh
    L_0043a162:
        test eax,eax
    L_0043a164:
        pop ebx
    L_0043a165:
        je short L_0043a16e
    L_0043a167:
        mov byte ptr [data_00492518],1
    L_0043a16e:
        mov eax,dword ptr [data_00491ff4]
    L_0043a173:
        and eax,0FFFFFFBFh
    L_0043a176:
        pop esi
    L_0043a177:
        jmp short L_0043a181
    L_0043a179:
        mov eax,dword ptr [data_00491ff4]
    L_0043a17e:
        or eax,40h
    L_0043a181:
        mov edx,dword ptr [data_00497ba8]
    L_0043a187:
        mov ecx,dword ptr [esp+258h]
    L_0043a18e:
        mov dword ptr [data_00491ff4],eax
    L_0043a193:
        xor eax,eax
    L_0043a195:
        test edx,edx
    L_0043a197:
        setne al
    L_0043a19a:
        pop edi
    L_0043a19b:
        xor ecx,esp
    L_0043a19d:
        dec eax
    L_0043a19e:
        call asm_security_check_cookie_00458ea5
    L_0043a1a3:
        add esp,258h
    L_0043a1a9:
        ret
    }
}

// 0x0043A290..0x0043A39F: FUN_0043a290
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a290_0043a290() {
    __asm {
    L_0043a290:
        sub esp,150h
    L_0043a296:
        mov eax,dword ptr [data_00473660]
    L_0043a29b:
        xor eax,esp
    L_0043a29d:
        test ebx,ebx
    L_0043a29f:
        push ebp
    L_0043a2a0:
        mov ebp,dword ptr [esp+158h]
    L_0043a2a7:
        mov dword ptr [esp+150h],eax
    L_0043a2ae:
        jne short L_0043a2ca
    L_0043a2b0:
        xor eax,eax
    L_0043a2b2:
        pop ebp
    L_0043a2b3:
        mov ecx,dword ptr [esp+14Ch]
    L_0043a2ba:
        xor ecx,esp
    L_0043a2bc:
        call asm_security_check_cookie_00458ea5
    L_0043a2c1:
        add esp,150h
    L_0043a2c7:
        ret 4
    L_0043a2ca:
        push 0
    L_0043a2cc:
        mov dword ptr [esp+10h],0
    L_0043a2d4:
        call dword ptr [data_00466308]
    L_0043a2da:
        lea eax,[esp+4]
    L_0043a2de:
        push eax
    L_0043a2df:
        push 46931Ch
    L_0043a2e4:
        push 1
    L_0043a2e6:
        push 0
    L_0043a2e8:
        push 46954Ch
    L_0043a2ed:
        call dword ptr [data_00466304]
    L_0043a2f3:
        test eax,eax
    L_0043a2f5:
        jl asm_target_0043a37e
    L_0043a2fb:
        mov eax,dword ptr [esp+4]
    L_0043a2ff:
        mov ecx,dword ptr [eax]
    L_0043a301:
        lea edx,[esp+8]
    L_0043a305:
        push edx
    L_0043a306:
        push 46997Ch
    L_0043a30b:
        push eax
    L_0043a30c:
        call dword ptr [ecx]
    L_0043a30e:
        test eax,eax
    L_0043a310:
        jl short L_0043a374
    L_0043a312:
        lea eax,[edi+edi]
    L_0043a315:
        push esi
    L_0043a316:
        push eax
    L_0043a317:
        call asm_operator_new_00452493
    L_0043a31c:
        add esp,4
    L_0043a31f:
        push edi
    L_0043a320:
        mov esi,eax
    L_0043a322:
        push esi
    L_0043a323:
        push 0FFFFFFFFh
    L_0043a325:
        push ebp
    L_0043a326:
        push 0
    L_0043a328:
        push 0
    L_0043a32a:
        call dword ptr [data_00466104]
    L_0043a330:
        mov eax,dword ptr [esp+0Ch]
    L_0043a334:
        mov ecx,dword ptr [eax]
    L_0043a336:
        push 0
    L_0043a338:
        push esi
    L_0043a339:
        push eax
    L_0043a33a:
        call dword ptr [ecx+14h]
    L_0043a33d:
        test eax,eax
    L_0043a33f:
        jl short L_0043a360
    L_0043a341:
        mov eax,dword ptr [esp+8]
    L_0043a345:
        mov edx,dword ptr [eax]
    L_0043a347:
        push 0
    L_0043a349:
        lea ecx,[esp+18h]
    L_0043a34d:
        push ecx
    L_0043a34e:
        push edi
    L_0043a34f:
        push ebx
    L_0043a350:
        push eax
    L_0043a351:
        call dword ptr [edx+0Ch]
    L_0043a354:
        test eax,eax
    L_0043a356:
        jl short L_0043a360
    L_0043a358:
        mov dword ptr [esp+10h],1
    L_0043a360:
        push esi
    L_0043a361:
        call asm_free_004524a1
    L_0043a366:
        mov eax,dword ptr [esp+10h]
    L_0043a36a:
        mov edx,dword ptr [eax]
    L_0043a36c:
        add esp,4
    L_0043a36f:
        push eax
    L_0043a370:
        call dword ptr [edx+8]
    L_0043a373:
        pop esi
    L_0043a374:
        mov eax,dword ptr [esp+4]
    L_0043a378:
        mov ecx,dword ptr [eax]
    L_0043a37a:
        push eax
    L_0043a37b:
        call dword ptr [ecx+8]
    L_0043a37e:
        call dword ptr [data_00466300]
    L_0043a384:
        mov ecx,dword ptr [esp+150h]
    L_0043a38b:
        mov eax,dword ptr [esp+0Ch]
    L_0043a38f:
        pop ebp
    L_0043a390:
        xor ecx,esp
    L_0043a392:
        call asm_security_check_cookie_00458ea5
    L_0043a397:
        add esp,150h
    L_0043a39d:
        ret 4
    }
}

// 0x0043AA60..0x0043AACA: FUN_0043aa60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043aa60_0043aa60() {
    __asm {
    L_0043aa60:
        mov eax,dword ptr [esi+118h]
    L_0043aa66:
        push ebx
    L_0043aa67:
        push ebp
    L_0043aa68:
        xor ebp,ebp
    L_0043aa6a:
        xor ebx,ebx
    L_0043aa6c:
        cmp eax,ebp
    L_0043aa6e:
        jle short L_0043aaa3
    L_0043aa70:
        push edi
    L_0043aa71:
        xor edi,edi
    L_0043aa73:
        mov eax,dword ptr [esi+138h]
    L_0043aa79:
        mov eax,dword ptr [edi+eax+10h]
    L_0043aa7d:
        cmp eax,ebp
    L_0043aa7f:
        je short L_0043aa94
    L_0043aa81:
        push eax
    L_0043aa82:
        call asm_free_00452422
    L_0043aa87:
        mov ecx,dword ptr [esi+138h]
    L_0043aa8d:
        add esp,4
    L_0043aa90:
        mov dword ptr [edi+ecx+10h],ebp
    L_0043aa94:
        mov eax,dword ptr [esi+118h]
    L_0043aa9a:
        inc ebx
    L_0043aa9b:
        add edi,20h
    L_0043aa9e:
        cmp ebx,eax
    L_0043aaa0:
        jl short L_0043aa73
    L_0043aaa2:
        pop edi
    L_0043aaa3:
        mov eax,dword ptr [esi+138h]
    L_0043aaa9:
        cmp eax,ebp
    L_0043aaab:
        je short L_0043aabc
    L_0043aaad:
        push eax
    L_0043aaae:
        call asm_free_00452422
    L_0043aab3:
        add esp,4
    L_0043aab6:
        mov dword ptr [esi+138h],ebp
    L_0043aabc:
        mov dword ptr [esi+138h],ebp
    L_0043aac2:
        mov dword ptr [esi+118h],ebp
    L_0043aac8:
        pop ebp
    L_0043aac9:
        pop ebx
    L_0043aaca:
        ret
    }
}

// 0x0043AE20..0x0043AEA0: FUN_0043ae20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ae20_0043ae20() {
    __asm {
    L_0043ae20:
        mov eax,dword ptr [edi+138h]
    L_0043ae26:
        test eax,eax
    L_0043ae28:
        jne short L_0043ae2e
    L_0043ae2a:
        or eax,0FFFFFFFFh
    L_0043ae2d:
        ret
    L_0043ae2e:
        push ebx
    L_0043ae2f:
        push ebp
    L_0043ae30:
        push esi
    L_0043ae31:
        lea ebx,[edi+14h]
    L_0043ae34:
        mov ebp,20h
    L_0043ae39:
        lea esp,[esp+force_disp32_zero]
    L_0043ae40:
        mov esi,dword ptr [ebx]
    L_0043ae42:
        test esi,esi
    L_0043ae44:
        je short L_0043ae4d
    L_0043ae46:
        mov edx,edi
    L_0043ae48:
        call asm_FUN_0043aeb0_0043aeb0
    L_0043ae4d:
        add ebx,4
    L_0043ae50:
        dec ebp
    L_0043ae51:
        jne short L_0043ae40
    L_0043ae53:
        mov eax,dword ptr [edi+4]
    L_0043ae56:
        test eax,eax
    L_0043ae58:
        je short L_0043ae61
    L_0043ae5a:
        push eax
    L_0043ae5b:
        call dword ptr [data_00466288]
    L_0043ae61:
        mov eax,dword ptr [edi+8]
    L_0043ae64:
        push eax
    L_0043ae65:
        call dword ptr [data_00466274]
    L_0043ae6b:
        xor esi,esi
    L_0043ae6d:
        mov dword ptr [edi+4],esi
    L_0043ae70:
        mov eax,dword ptr [edi+13Ch]
    L_0043ae76:
        cmp eax,esi
    L_0043ae78:
        je short L_0043ae94
    L_0043ae7a:
        push eax
    L_0043ae7b:
        call dword ptr [data_004662a8]
    L_0043ae81:
        mov ecx,dword ptr [edi+13Ch]
    L_0043ae87:
        push ecx
    L_0043ae88:
        call dword ptr [data_004662a4]
    L_0043ae8e:
        mov dword ptr [edi+13Ch],esi
    L_0043ae94:
        pop esi
    L_0043ae95:
        pop ebp
    L_0043ae96:
        mov dword ptr [edi+10h],0FFFFFFFFh
    L_0043ae9d:
        xor eax,eax
    L_0043ae9f:
        pop ebx
    L_0043aea0:
        ret
    }
}

// 0x0043AEB0..0x0043AEFE: FUN_0043aeb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043aeb0_0043aeb0() {
    __asm {
    L_0043aeb0:
        xor eax,eax
    L_0043aeb2:
        lea ecx,[edx+14h]
    L_0043aeb5:
        cmp dword ptr [ecx],esi
    L_0043aeb7:
        je short L_0043aec6
    L_0043aeb9:
        inc eax
    L_0043aeba:
        add ecx,4
    L_0043aebd:
        cmp eax,20h
    L_0043aec0:
        jl short L_0043aeb5
    L_0043aec2:
        or eax,0FFFFFFFFh
    L_0043aec5:
        ret
    L_0043aec6:
        push 40h
    L_0043aec8:
        mov dword ptr [edx+eax*4+14h],0
    L_0043aed0:
        mov eax,dword ptr [edx+13Ch]
    L_0043aed6:
        push esi
    L_0043aed7:
        push eax
    L_0043aed8:
        call dword ptr [data_00466284]
    L_0043aede:
        mov eax,dword ptr [esi]
    L_0043aee0:
        test eax,eax
    L_0043aee2:
        je short L_0043aef3
    L_0043aee4:
        push eax
    L_0043aee5:
        call asm_free_00452422
    L_0043aeea:
        add esp,4
    L_0043aeed:
        mov dword ptr [esi],0
    L_0043aef3:
        push esi
    L_0043aef4:
        call asm_free_00452422
    L_0043aef9:
        add esp,4
    L_0043aefc:
        xor eax,eax
    L_0043aefe:
        ret
    }
}
