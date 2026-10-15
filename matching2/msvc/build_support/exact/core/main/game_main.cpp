#include "th10/source_views/window_exact_0.hpp"
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
        mov ebx,dword ptr [imp_InitializeCriticalSection]
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
        mov dword ptr [g_application],esi
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
        call dword ptr [imp_DialogBoxParamA]
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
        call asm_FuncCtrl_Construct
    L_00438bb8:
        jmp short L_00438bbc
    L_00438bba:
        xor eax,eax
    L_00438bbc:
        push 20h
    L_00438bbe:
        mov dword ptr [g_func_ctrl],eax
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
        call dword ptr [imp_CreateThread]
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
        call asm_SprtCtrl_Construct
    L_00438c5c:
        jmp short L_00438c60
    L_00438c5e:
        xor eax,eax
    L_00438c60:
        mov dword ptr [g_sprt_ctrl],eax
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
        call dword ptr [imp_ShowCursor]
    L_00438c7b:
        push ebx
    L_00438c7c:
        call dword ptr [imp_SetCursor]
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
        call dword ptr [imp_SetForegroundWindow]
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
        call dword ptr [imp_PeekMessageA]
    L_00438d01:
        test eax,eax
    L_00438d03:
        je short L_00438d1d
    L_00438d05:
        lea edx,[esp+14h]
    L_00438d09:
        push edx
    L_00438d0a:
        call dword ptr [imp_TranslateMessage]
    L_00438d10:
        lea eax,[esp+14h]
    L_00438d14:
        push eax
    L_00438d15:
        call dword ptr [imp_DispatchMessageA]
    L_00438d1b:
        jmp short L_00438d89
    L_00438d1d:
        mov eax,dword ptr [g_d3d_device]
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
        mov eax,dword ptr [g_sprt_ctrl]
    L_00438d54:
        call asm_DestroyEntityList_00438a30
    L_00438d59:
        mov eax,dword ptr [g_d3d_device]
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
        mov eax,dword ptr [g_func_ctrl]
    L_00438da4:
        cmp eax,ebx
    L_00438da6:
        mov esi,eax
    L_00438da8:
        je short L_00438db9
    L_00438daa:
        push eax
    L_00438dab:
        call asm_FuncCtrlDestroyView
    L_00438db0:
        push esi
    L_00438db1:
        call asm_free_004524a1
    L_00438db6:
        add esp,4
    L_00438db9:
        mov dword ptr [g_func_ctrl],ebx
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
        mov eax,dword ptr [g_sprt_ctrl]
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
        mov eax,dword ptr [g_d3d_device]
    L_00438e0b:
        cmp eax,ebp
    L_00438e0d:
        mov dword ptr [g_sprt_ctrl],ebp
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
        mov eax,dword ptr [g_d3d_device]
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
        mov dword ptr [g_d3d_device],ebp
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
        call dword ptr [imp_ShowWindow]
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
        call dword ptr [imp_MoveWindow]
    L_00438e6d:
        mov eax,dword ptr [data_004924f0]
    L_00438e72:
        push eax
    L_00438e73:
        call dword ptr [imp_DestroyWindow]
    L_00438e79:
        mov dword ptr [data_004924f0],ebp
    L_00438e7f:
        push 1
    L_00438e81:
        call dword ptr [imp_ShowCursor]
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
        mov byte ptr [g_log],0
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
        mov edi,dword ptr [imp_PeekMessageA]
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
        call dword ptr [imp_TranslateMessage]
    L_00438ee3:
        lea eax,[esp+14h]
    L_00438ee7:
        push eax
    L_00438ee8:
        call dword ptr [imp_DispatchMessageA]
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
        call dword ptr [imp_MessageBoxA]
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
        mov ebp,dword ptr [imp_DeleteCriticalSection]
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
        mov esi,dword ptr [imp_SystemParametersInfoA]
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
        _emit 0x8d
        _emit 0x49
        _emit 0x00

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
