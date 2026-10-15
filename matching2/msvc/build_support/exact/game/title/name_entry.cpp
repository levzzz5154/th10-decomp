#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"



// 0x00432CB0..0x00433215: FUN_00432cb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00432cb0_00432cb0() {
    __asm {
    L_00432cb0:
        push ecx
    L_00432cb1:
        push ebp
    L_00432cb2:
        mov ebp,dword ptr [esp+0Ch]
    L_00432cb6:
        mov eax,dword ptr [ebp+20h]
    L_00432cb9:
        cmp eax,3
    L_00432cbc:
        ja asm_target_0043320c
    L_00432cc2:
        push ebx
    L_00432cc3:
        push esi
    L_00432cc4:
        push edi
    L_00432cc5:
        jmp dword ptr [eax*4+433218h]
    L_00432ccc:
        push 46E0D8h
    L_00432cd1:
        xor ebx,ebx
    L_00432cd3:
        push ebx
    L_00432cd4:
        mov dword ptr [ebp+2Ch],1Eh
    L_00432cdb:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_00432ce0:
        push 11h
    L_00432ce2:
        push ebx
    L_00432ce3:
        call asm_Sound_PlayDummyRetail_00420b10
    L_00432ce8:
        mov eax,dword ptr [ebp+43Ch]
    L_00432cee:
        mov edx,dword ptr [g_sprt_ctrl]
    L_00432cf4:
        push eax
    L_00432cf5:
        call asm_AnimationManager_Find_004491c0
    L_00432cfa:
        test eax,eax
    L_00432cfc:
        jne short L_00432d2b
    L_00432cfe:
        push ebp
    L_00432cff:
        mov edi,5Eh
    L_00432d04:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432d09:
        mov ecx,dword ptr [g_ascii_manager]
    L_00432d0f:
        mov eax,dword ptr [ecx+8994h]
    L_00432d15:
        push 0Fh
    L_00432d17:
        push 8
    L_00432d19:
        push eax
    L_00432d1a:
        lea edi,[esp+1Ch]
    L_00432d1e:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00432d23:
        mov edx,dword ptr [eax]
    L_00432d25:
        mov dword ptr [ebp+5D0h],edx
    L_00432d2b:
        push ebp
    L_00432d2c:
        mov edi,68h
    L_00432d31:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432d36:
        mov ecx,1
    L_00432d3b:
        mov eax,ebp
    L_00432d3d:
        call asm_GameState_SetTimerTarget_0042c620
    L_00432d42:
        mov edi,dword ptr [g_globals_character]
    L_00432d48:
        add edi,98h
    L_00432d4e:
        push ebp
    L_00432d4f:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432d54:
        mov eax,dword ptr [g_globals_character]
    L_00432d59:
        mov ecx,dword ptr [g_globals_shot_type]
    L_00432d5f:
        lea edx,[ecx+eax*2]
    L_00432d62:
        lea edi,[eax+edx+9Ah]
    L_00432d69:
        push ebp
    L_00432d6a:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432d6f:
        mov edi,dword ptr [g_globals_difficulty]
    L_00432d75:
        add edi,0A0h
    L_00432d7b:
        push ebp
    L_00432d7c:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00432d81:
        mov ecx,dword ptr [g_globals_shot_type]
    L_00432d87:
        mov eax,8
    L_00432d8c:
        mov dword ptr [g_globals_stage],eax
    L_00432d91:
        mov dword ptr [g_globals_stage_shown],eax
    L_00432d96:
        mov eax,dword ptr [g_globals_character]
    L_00432d9b:
        lea edx,[ecx+eax*2]
    L_00432d9e:
        add edx,eax
    L_00432da0:
        mov eax,dword ptr [g_score]
    L_00432da5:
        imul edx,437Ch
    L_00432dab:
        lea edi,[edx+eax+8]
    L_00432daf:
        mov dword ptr [data_00477848],474908h
    L_00432db9:
        call asm_FUN_00421fa0_00421fa0
    L_00432dbe:
        mov esi,eax
    L_00432dc0:
        cmp esi,ebx
    L_00432dc2:
        mov dword ptr [data_00477848],474788h
    L_00432dcc:
        mov dword ptr [g_globals_stage],ebx
    L_00432dd2:
        mov dword ptr [g_globals_stage_shown],ebx
    L_00432dd8:
        jl asm_target_00432eb0
    L_00432dde:
        push ebx
    L_00432ddf:
        lea eax,[ebp+2B0h]
    L_00432de5:
        call asm_Player_SetSchedulerValue_00405410
    L_00432dea:
        lea edx,[ebp+24h]
    L_00432ded:
        mov ecx,esi
    L_00432def:
        mov dword ptr [ebp+0F4h],1
    L_00432df9:
        call asm_FUN_0040ad20_0040ad20
    L_00432dfe:
        mov eax,dword ptr [ebp+58FCh]
    L_00432e04:
        test eax,eax
    L_00432e06:
        lea ebx,[ebp+58F4h]
    L_00432e0c:
        je short L_00432e1b
    L_00432e0e:
        jg short L_00432e15
    L_00432e10:
        dec eax
    L_00432e11:
        mov dword ptr [ebx],eax
    L_00432e13:
        jmp short L_00432e21
    L_00432e15:
        xor eax,eax
    L_00432e17:
        mov dword ptr [ebx],eax
    L_00432e19:
        jmp short L_00432e21
    L_00432e1b:
        mov dword ptr [ebx],0
    L_00432e21:
        mov ecx,dword ptr [data_004746d8]
    L_00432e27:
        lea edx,[ecx+1]
    L_00432e2a:
        lea ebx,[ebx+force_disp32_zero]
    L_00432e30:
        mov al,byte ptr [ecx]
    L_00432e32:
        inc ecx
    L_00432e33:
        test al,al
    L_00432e35:
        jne short L_00432e30
    L_00432e37:
        sub ecx,edx
    L_00432e39:
        mov dword ptr [ebp+58FCh],ecx
    L_00432e3f:
        mov ecx,dword ptr [g_score]
    L_00432e45:
        lea esi,[ebp+58DCh]
    L_00432e4b:
        add ecx,1D878h
    L_00432e51:
        mov edx,esi
    L_00432e53:
        mov dword ptr [ebp+59C4h],1
    L_00432e5d:
        sub edx,ecx
    L_00432e5f:
        nop
    L_00432e60:
        mov al,byte ptr [ecx]
    L_00432e62:
        mov byte ptr [edx+ecx],al
    L_00432e65:
        inc ecx
    L_00432e66:
        test al,al
    L_00432e68:
        jne short L_00432e60
    L_00432e6a:
        mov edi,46E354h
    L_00432e6f:
        mov ecx,9
    L_00432e74:
        xor edx,edx
    L_00432e76:
        repe cmpsb
    L_00432e78:
        je short L_00432e83
    L_00432e7a:
        push 0FFFFFFFFh
    L_00432e7c:
        mov eax,ebx
    L_00432e7e:
        call asm_MenuCursor_Advance_0044bea0
    L_00432e83:
        mov eax,8
    L_00432e88:
        mov ebx,20h
    L_00432e8d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00432e90:
        cmp byte ptr [eax+ebp+58DBh],bl
    L_00432e97:
        jne short L_00432e9e
    L_00432e99:
        dec eax
    L_00432e9a:
        test eax,eax
    L_00432e9c:
        jg short L_00432e90
    L_00432e9e:
        mov dword ptr [ebp+58E8h],eax
    L_00432ea4:
        mov dword ptr [ebp+58ECh],0
    L_00432eae:
        jmp short L_00432eda
    L_00432eb0:
        mov eax,dword ptr [ebp+2Ch]
    L_00432eb3:
        cmp eax,ebx
    L_00432eb5:
        je short L_00432ec9
    L_00432eb7:
        cmp eax,0FFFFFFFFh
    L_00432eba:
        jg short L_00432ec2
    L_00432ebc:
        dec eax
    L_00432ebd:
        mov dword ptr [ebp+24h],eax
    L_00432ec0:
        jmp short L_00432ed0
    L_00432ec2:
        xor eax,eax
    L_00432ec4:
        mov dword ptr [ebp+24h],eax
    L_00432ec7:
        jmp short L_00432ed0
    L_00432ec9:
        mov dword ptr [ebp+24h],0FFFFFFFFh
    L_00432ed0:
        mov dword ptr [ebp+58ECh],1
    L_00432eda:
        cmp dword ptr [ebp+2B4h],6
    L_00432ee1:
        jle asm_target_00433209
    L_00432ee7:
        mov ecx,2
    L_00432eec:
        mov eax,ebp
    L_00432eee:
        call asm_GameState_SetTimerTarget_0042c620
    L_00432ef3:
        pop edi
    L_00432ef4:
        pop esi
    L_00432ef5:
        pop ebx
    L_00432ef6:
        mov eax,1
    L_00432efb:
        pop ebp
    L_00432efc:
        pop ecx
    L_00432efd:
        ret 4
    L_00432f00:
        mov eax,dword ptr [ebp+58ECh]
    L_00432f06:
        test eax,eax
    L_00432f08:
        mov ebx,20h
    L_00432f0d:
        jne asm_target_00432fd0
    L_00432f13:
        mov eax,dword ptr [ebp+58F4h]
    L_00432f19:
        lea esi,[ebp+58F4h]
    L_00432f1f:
        mov dword ptr [esi+4],eax
    L_00432f22:
        mov eax,10h
    L_00432f27:
        mov ecx,474E30h
    L_00432f2c:
        call asm_InputMaskActive_0040ace0
    L_00432f31:
        test ax,ax
    L_00432f34:
        je short L_00432f3f
    L_00432f36:
        push 0FFFFFFF3h
    L_00432f38:
        mov eax,esi
    L_00432f3a:
        call asm_MenuCursor_Advance_0044bea0
    L_00432f3f:
        mov eax,ebx
    L_00432f41:
        mov ecx,474E30h
    L_00432f46:
        call asm_InputMaskActive_0040ace0
    L_00432f4b:
        test ax,ax
    L_00432f4e:
        je short L_00432f59
    L_00432f50:
        push 0Dh
    L_00432f52:
        mov eax,esi
    L_00432f54:
        call asm_MenuCursor_Advance_0044bea0
    L_00432f59:
        mov eax,40h
    L_00432f5e:
        mov ecx,474E30h
    L_00432f63:
        call asm_InputMaskActive_0040ace0
    L_00432f68:
        test ax,ax
    L_00432f6b:
        je short L_00432f88
    L_00432f6d:
        mov eax,dword ptr [esi]
    L_00432f6f:
        cdq
    L_00432f70:
        mov ecx,0Dh
    L_00432f75:
        idiv ecx
    L_00432f77:
        mov eax,esi
    L_00432f79:
        test edx,edx
    L_00432f7b:
        je short L_00432f81
    L_00432f7d:
        push 0FFFFFFFFh
    L_00432f7f:
        jmp short L_00432f83
    L_00432f81:
        push 0Ch
    L_00432f83:
        call asm_MenuCursor_Advance_0044bea0
    L_00432f88:
        mov eax,80h
    L_00432f8d:
        mov ecx,474E30h
    L_00432f92:
        call asm_InputMaskActive_0040ace0
    L_00432f97:
        test ax,ax
    L_00432f9a:
        je short L_00432fb8
    L_00432f9c:
        mov eax,dword ptr [esi]
    L_00432f9e:
        cdq
    L_00432f9f:
        mov ecx,0Dh
    L_00432fa4:
        idiv ecx
    L_00432fa6:
        mov eax,esi
    L_00432fa8:
        cmp edx,0Ch
    L_00432fab:
        je short L_00432fb1
    L_00432fad:
        push 1
    L_00432faf:
        jmp short L_00432fb3
    L_00432fb1:
        push 0FFFFFFF4h
    L_00432fb3:
        call asm_MenuCursor_Advance_0044bea0
    L_00432fb8:
        mov edx,dword ptr [esi+4]
    L_00432fbb:
        cmp edx,dword ptr [esi]
    L_00432fbd:
        je short L_00432fd0
    L_00432fbf:
        push 0
    L_00432fc1:
        mov edi,0Ch
    L_00432fc6:
        mov ecx,492590h
    L_00432fcb:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00432fd0:
        test dword ptr [data_00474e36],1001h
    L_00432fda:
        je asm_target_0043312b
    L_00432fe0:
        mov eax,dword ptr [ebp+58ECh]
    L_00432fe6:
        test eax,eax
    L_00432fe8:
        jne asm_target_0043310e
    L_00432fee:
        mov edi,dword ptr [data_004746d8]
    L_00432ff4:
        mov eax,edi
    L_00432ff6:
        lea edx,[eax+1]
    L_00432ff9:
        lea esp,[esp+force_disp32_zero]
    L_00433000:
        mov cl,byte ptr [eax]
    L_00433002:
        inc eax
    L_00433003:
        test cl,cl
    L_00433005:
        jne short L_00433000
    L_00433007:
        mov ecx,dword ptr [ebp+58F4h]
    L_0043300d:
        sub eax,edx
    L_0043300f:
        lea edx,[ebp+58F4h]
    L_00433015:
        lea esi,[eax-3]
    L_00433018:
        cmp ecx,esi
    L_0043301a:
        jge short L_00433042
    L_0043301c:
        mov esi,dword ptr [ebp+58E8h]
    L_00433022:
        cmp esi,8
    L_00433025:
        jge short L_00433033
    L_00433027:
        mov cl,byte ptr [ecx+edi]
    L_0043302a:
        mov byte ptr [esi+ebp+58DCh],cl
    L_00433031:
        jmp short L_00433056
    L_00433033:
        mov dl,byte ptr [ecx+edi]
    L_00433036:
        mov byte ptr [esi+ebp+58DBh],dl
    L_0043303d:
        jmp asm_target_0043311a
    L_00433042:
        jne short L_00433087
    L_00433044:
        mov ecx,dword ptr [ebp+58E8h]
    L_0043304a:
        cmp ecx,8
    L_0043304d:
        jge short L_0043307b
    L_0043304f:
        mov byte ptr [ecx+ebp+58DCh],bl
    L_00433056:
        mov esi,dword ptr [ebp+58E8h]
    L_0043305c:
        inc esi
    L_0043305d:
        mov ecx,esi
    L_0043305f:
        cmp ecx,8
    L_00433062:
        mov dword ptr [ebp+58E8h],esi
    L_00433068:
        jl asm_target_0043311a
    L_0043306e:
        lea ecx,[eax-1]
    L_00433071:
        call asm_FUN_0040ad20_0040ad20
    L_00433076:
        jmp asm_target_0043311a
    L_0043307b:
        mov byte ptr [ecx+ebp+58DBh],bl
    L_00433082:
        jmp asm_target_0043311a
    L_00433087:
        lea edx,[eax-2]
    L_0043308a:
        cmp ecx,edx
    L_0043308c:
        jne short L_004330ac
    L_0043308e:
        mov eax,dword ptr [ebp+58E8h]
    L_00433094:
        test eax,eax
    L_00433096:
        je asm_target_00433209
    L_0043309c:
        dec eax
    L_0043309d:
        mov dword ptr [ebp+58E8h],eax
    L_004330a3:
        mov byte ptr [eax+ebp+58DCh],bl
    L_004330aa:
        jmp short L_0043311a
    L_004330ac:
        dec eax
    L_004330ad:
        cmp ecx,eax
    L_004330af:
        jne short L_0043311a
    L_004330b1:
        mov ecx,dword ptr [g_globals_difficulty]
    L_004330b7:
        mov edi,dword ptr [g_globals_shot_type]
    L_004330bd:
        lea eax,[ecx+ecx*4]
    L_004330c0:
        mov ecx,dword ptr [ebp+24h]
    L_004330c3:
        lea ecx,[ecx+eax*2]
    L_004330c6:
        lea eax,[ecx+ecx*2]
    L_004330c9:
        mov ecx,dword ptr [g_globals_character]
    L_004330cf:
        lea edi,[edi+ecx*2]
    L_004330d2:
        add edi,ecx
    L_004330d4:
        imul edi,437Ch
    L_004330da:
        mov ecx,edi
    L_004330dc:
        mov edi,dword ptr [g_score]
    L_004330e2:
        lea esi,[ebp+58DCh]
    L_004330e8:
        add ecx,edi
    L_004330ea:
        mov edx,esi
    L_004330ec:
        lea ecx,[ecx+eax*8+1Eh]
    L_004330f0:
        mov al,byte ptr [edx]
    L_004330f2:
        inc edx
    L_004330f3:
        mov byte ptr [ecx],al
    L_004330f5:
        inc ecx
    L_004330f6:
        test al,al
    L_004330f8:
        jne short L_004330f0
    L_004330fa:
        lea edx,[edi+1D878h]
    L_00433100:
        mov eax,esi
    L_00433102:
        sub edx,esi
    L_00433104:
        mov cl,byte ptr [eax]
    L_00433106:
        mov byte ptr [edx+eax],cl
    L_00433109:
        inc eax
    L_0043310a:
        test cl,cl
    L_0043310c:
        jne short L_00433104
    L_0043310e:
        mov eax,ebp
    L_00433110:
        mov ecx,3
    L_00433115:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043311a:
        mov ecx,492590h
    L_0043311f:
        mov edi,0Ah
    L_00433124:
        push 0
    L_00433126:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043312b:
        test byte ptr [data_00474e36],0Ah
    L_00433132:
        je asm_target_00433209
    L_00433138:
        mov eax,dword ptr [ebp+58ECh]
    L_0043313e:
        test eax,eax
    L_00433140:
        jne short L_00433182
    L_00433142:
        mov eax,dword ptr [ebp+58E8h]
    L_00433148:
        test eax,eax
    L_0043314a:
        je asm_target_00433209
    L_00433150:
        push 0
    L_00433152:
        mov edi,0Bh
    L_00433157:
        mov ecx,492590h
    L_0043315c:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00433161:
        mov eax,dword ptr [ebp+58E8h]
    L_00433167:
        dec eax
    L_00433168:
        pop edi
    L_00433169:
        mov dword ptr [ebp+58E8h],eax
    L_0043316f:
        mov byte ptr [eax+ebp+58DCh],bl
    L_00433176:
        pop esi
    L_00433177:
        pop ebx
    L_00433178:
        mov eax,1
    L_0043317d:
        pop ebp
    L_0043317e:
        pop ecx
    L_0043317f:
        ret 4
    L_00433182:
        mov ecx,3
    L_00433187:
        mov eax,ebp
    L_00433189:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043318e:
        push 0
    L_00433190:
        mov edi,0Ah
    L_00433195:
        mov ecx,492590h
    L_0043319a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043319f:
        pop edi
    L_004331a0:
        pop esi
    L_004331a1:
        pop ebx
    L_004331a2:
        mov eax,1
    L_004331a7:
        pop ebp
    L_004331a8:
        pop ecx
    L_004331a9:
        ret 4
    L_004331ac:
        cmp dword ptr [ebp+2B4h],6
    L_004331b3:
        jl short L_00433209
    L_004331b5:
        mov esi,68h
    L_004331ba:
        mov edi,ebp
    L_004331bc:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004331c1:
        mov esi,dword ptr [g_globals_character]
    L_004331c7:
        add esi,98h
    L_004331cd:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004331d2:
        mov eax,dword ptr [g_globals_character]
    L_004331d7:
        mov ecx,dword ptr [g_globals_shot_type]
    L_004331dd:
        lea edx,[ecx+eax*2]
    L_004331e0:
        lea esi,[eax+edx+9Ah]
    L_004331e7:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004331ec:
        mov esi,dword ptr [g_globals_difficulty]
    L_004331f2:
        add esi,0A0h
    L_004331f8:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_004331fd:
        mov ecx,10h
    L_00433202:
        mov eax,ebp
    L_00433204:
        call asm_Title_DisableTimerWithOwner
    L_00433209:
        pop edi
    L_0043320a:
        pop esi
    L_0043320b:
        pop ebx
    L_0043320c:
        mov eax,1
    L_00433211:
        pop ebp
    L_00433212:
        pop ecx
    L_00433213:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0xcc
        _emit 0x2c
        _emit 0x43
        _emit 0x00
        _emit 0xda
        _emit 0x2e
        _emit 0x43
        _emit 0x00
        _emit 0x00
        _emit 0x2f
        _emit 0x43
        _emit 0x00
        _emit 0xac
        _emit 0x31
        _emit 0x43
        _emit 0x00
    }
}
