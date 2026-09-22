#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D920..0x0042DA27: FUN_0042d920
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3901): closest_byte_count=0/3188; first_diff=unmeasured;
// residual_class=large options state machine, private animation-manager
// receiver/frame conventions, and timer/input helper ABIs across the handler's
// jump-table and phase transitions. variants_tested=exact retail assembly
// probe (3188/3188), legacy semantic title-options model, live caller topology
// at 0x0042D13F, and dependency review for 0x0042C5C0/0x0042C670/
// 0x0042C730/0x0042C750/0x0042C770/0x00449250; no readable candidate was
// byte-measured without changing the fixed-address ownership manifest.
// next_lever=schema-2/native-LTCG cluster with real caller 0x0042D13F and the
// timer/animation manager callees co-compiled, retaining the complete
// 3188-byte contribution.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d920_0042d920() {
    __asm {
    L_0042d920:
        push ebp
    L_0042d921:
        mov ebp,dword ptr [esp+8]
    L_0042d925:
        mov eax,dword ptr [ebp+20h]
    L_0042d928:
        cmp eax,4
    L_0042d92b:
        ja asm_target_0042e577
    L_0042d931:
        push ebx
    L_0042d932:
        push esi
    L_0042d933:
        push edi
    L_0042d934:
        mov esi,6
    L_0042d939:
        xor ebx,ebx
    L_0042d93b:
        jmp dword ptr [eax*4+42E580h]
    L_0042d942:
        mov eax,esi
    L_0042d944:
        cmp eax,ebx
    L_0042d946:
        mov dword ptr [ebp+2Ch],esi
    L_0042d949:
        je short L_0042d95a
    L_0042d94b:
        jg short L_0042d953
    L_0042d94d:
        dec eax
    L_0042d94e:
        mov dword ptr [ebp+24h],eax
    L_0042d951:
        jmp short L_0042d95d
    L_0042d953:
        xor eax,eax
    L_0042d955:
        mov dword ptr [ebp+24h],eax
    L_0042d958:
        jmp short L_0042d95d
    L_0042d95a:
        mov dword ptr [ebp+24h],ebx
    L_0042d95d:
        push ebp
    L_0042d95e:
        mov edi,1
    L_0042d963:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d968:
        mov edi,ebp
    L_0042d96a:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042d96f:
        mov ecx,1
    L_0042d974:
        mov eax,ebp
    L_0042d976:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d97b:
        cmp dword ptr [ebp+2B4h],esi
    L_0042d981:
        jle asm_target_0042e574
    L_0042d987:
        mov ecx,2
    L_0042d98c:
        mov eax,ebp
    L_0042d98e:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042d993:
        mov eax,dword ptr [ebp+2C8h]
    L_0042d999:
        mov edx,dword ptr [data_00491c10]
    L_0042d99f:
        push eax
    L_0042d9a0:
        mov edi,3
    L_0042d9a5:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042d9aa:
        mov al,byte ptr [data_00491d6a]
    L_0042d9af:
        cmp al,bl
    L_0042d9b1:
        mov esi,dword ptr [data_00491c10]
    L_0042d9b7:
        jne asm_target_0042da66
    L_0042d9bd:
        mov ecx,dword ptr [ebp+2C8h]
    L_0042d9c3:
        push ecx
    L_0042d9c4:
        mov edx,esi
    L_0042d9c6:
        call asm_AnimationManager_Find_004491c0
    L_0042d9cb:
        cmp eax,ebx
    L_0042d9cd:
        jne short L_0042d9d5
    L_0042d9cf:
        mov dword ptr [ebp+2C8h],ebx
    L_0042d9d5:
        add eax,10h
    L_0042d9d8:
        cmp eax,ebx
    L_0042d9da:
        je short L_0042d9f3
    L_0042d9dc:
        mov ecx,1Fh
    L_0042d9e1:
        mov edx,dword ptr [eax]
    L_0042d9e3:
        cmp word ptr [edx+38Ah],cx
    L_0042d9ea:
        TH10_REL8(0x74, 0x0042d9ea, VA_asm_target_0042da4d)
    L_0042d9ec:
        mov eax,dword ptr [eax+4]
    L_0042d9ef:
        cmp eax,ebx
    L_0042d9f1:
        jne short L_0042d9e1
    L_0042d9f3:
        mov dword ptr [esp+14h],ebx
    L_0042d9f7:
        push 2Eh
    L_0042d9f9:
        lea eax,[esp+18h]
    L_0042d9fd:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042da02:
        mov edx,dword ptr [ebp+2C8h]
    L_0042da08:
        push edx
    L_0042da09:
        mov edx,esi
    L_0042da0b:
        call asm_AnimationManager_Find_004491c0
    L_0042da10:
        cmp eax,ebx
    L_0042da12:
        jne short L_0042da1a
    L_0042da14:
        mov dword ptr [ebp+2C8h],ebx
    L_0042da1a:
        add eax,10h
    L_0042da1d:
        cmp eax,ebx
    L_0042da1f:
        TH10_REL8(0x74, 0x0042da1f, VA_asm_target_0042da42)
    L_0042da21:
        mov ecx,20h
    L_0042da26:
        TH10_REL8(0xeb, 0x0042da26, VA_asm_FUN_0042d920_part_0042da30)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0042da30:
        mov edx,dword ptr [eax]
    L_0042da32:
        cmp word ptr [edx+38Ah],cx
    L_0042da39:
        je short L_0042da57
    L_0042da3b:
        mov eax,dword ptr [eax+4]
    L_0042da3e:
        cmp eax,ebx
    L_0042da40:
        jne short L_0042da30
    L_0042da42:
        mov dword ptr [esp+14h],ebx
    L_0042da46:
        push 2Fh
    L_0042da48:
        jmp asm_target_0042db8d
    L_0042da4d:
        mov eax,dword ptr [eax]
    L_0042da4f:
        mov ecx,dword ptr [eax]
    L_0042da51:
        mov dword ptr [esp+14h],ecx
    L_0042da55:
        TH10_REL8(0xeb, 0x0042da55, VA_asm_target_0042d9f7)
    L_0042da57:
        mov eax,dword ptr [eax]
    L_0042da59:
        mov ecx,dword ptr [eax]
    L_0042da5b:
        mov dword ptr [esp+14h],ecx
    L_0042da5f:
        push 2Fh
    L_0042da61:
        jmp asm_target_0042db8d
    L_0042da66:
        cmp al,1
    L_0042da68:
        mov edx,dword ptr [ebp+2C8h]
    L_0042da6e:
        push edx
    L_0042da6f:
        mov edx,esi
    L_0042da71:
        jne asm_target_0042db13
    L_0042da77:
        call asm_AnimationManager_Find_004491c0
    L_0042da7c:
        cmp eax,ebx
    L_0042da7e:
        jne short L_0042da86
    L_0042da80:
        mov dword ptr [ebp+2C8h],ebx
    L_0042da86:
        add eax,10h
    L_0042da89:
        cmp eax,ebx
    L_0042da8b:
        je short L_0042daa4
    L_0042da8d:
        mov ecx,1Fh
    L_0042da92:
        mov edx,dword ptr [eax]
    L_0042da94:
        cmp word ptr [edx+38Ah],cx
    L_0042da9b:
        TH10_REL8(0x74, 0x0042da9b, VA_asm_target_0042dafd)
    L_0042da9d:
        mov eax,dword ptr [eax+4]
    L_0042daa0:
        cmp eax,ebx
    L_0042daa2:
        jne short L_0042da92
    L_0042daa4:
        mov dword ptr [esp+14h],ebx
    L_0042daa8:
        push 30h
    L_0042daaa:
        lea eax,[esp+18h]
    L_0042daae:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042dab3:
        mov edx,dword ptr [ebp+2C8h]
    L_0042dab9:
        push edx
    L_0042daba:
        mov edx,esi
    L_0042dabc:
        call asm_AnimationManager_Find_004491c0
    L_0042dac1:
        cmp eax,ebx
    L_0042dac3:
        jne short L_0042dacb
    L_0042dac5:
        mov dword ptr [ebp+2C8h],ebx
    L_0042dacb:
        add eax,10h
    L_0042dace:
        cmp eax,ebx
    L_0042dad0:
        TH10_REL8(0x74, 0x0042dad0, VA_asm_target_0042daf2)
    L_0042dad2:
        mov ecx,20h
    L_0042dad7:
        TH10_REL8(0xeb, 0x0042dad7, VA_asm_FUN_0042d920_part_0042dae0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042dae0:
        mov edx,dword ptr [eax]
    L_0042dae2:
        cmp word ptr [edx+38Ah],cx
    L_0042dae9:
        je short L_0042db07
    L_0042daeb:
        mov eax,dword ptr [eax+4]
    L_0042daee:
        cmp eax,ebx
    L_0042daf0:
        jne short L_0042dae0
    L_0042daf2:
        mov dword ptr [esp+14h],ebx
    L_0042daf6:
        push 31h
    L_0042daf8:
        jmp asm_target_0042db8d
    L_0042dafd:
        mov eax,dword ptr [eax]
    L_0042daff:
        mov ecx,dword ptr [eax]
    L_0042db01:
        mov dword ptr [esp+14h],ecx
    L_0042db05:
        TH10_REL8(0xeb, 0x0042db05, VA_asm_target_0042daa8)
    L_0042db07:
        mov eax,dword ptr [eax]
    L_0042db09:
        mov ecx,dword ptr [eax]
    L_0042db0b:
        mov dword ptr [esp+14h],ecx
    L_0042db0f:
        push 31h
    L_0042db11:
        jmp short L_0042db8d
    L_0042db13:
        call asm_AnimationManager_Find_004491c0
    L_0042db18:
        cmp eax,ebx
    L_0042db1a:
        jne short L_0042db22
    L_0042db1c:
        mov dword ptr [ebp+2C8h],ebx
    L_0042db22:
        add eax,10h
    L_0042db25:
        cmp eax,ebx
    L_0042db27:
        je short L_0042db42
    L_0042db29:
        mov ecx,1Fh
    L_0042db2e:
        mov edi,edi
    L_0042db30:
        mov edx,dword ptr [eax]
    L_0042db32:
        cmp word ptr [edx+38Ah],cx
    L_0042db39:
        je short L_0042dbb8
    L_0042db3b:
        mov eax,dword ptr [eax+4]
    L_0042db3e:
        cmp eax,ebx
    L_0042db40:
        jne short L_0042db30
    L_0042db42:
        mov dword ptr [esp+14h],ebx
    L_0042db46:
        push 2Ch
    L_0042db48:
        lea eax,[esp+18h]
    L_0042db4c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042db51:
        mov edx,dword ptr [ebp+2C8h]
    L_0042db57:
        push edx
    L_0042db58:
        mov edx,esi
    L_0042db5a:
        call asm_AnimationManager_Find_004491c0
    L_0042db5f:
        cmp eax,ebx
    L_0042db61:
        jne short L_0042db69
    L_0042db63:
        mov dword ptr [ebp+2C8h],ebx
    L_0042db69:
        add eax,10h
    L_0042db6c:
        cmp eax,ebx
    L_0042db6e:
        je short L_0042db87
    L_0042db70:
        mov ecx,20h
    L_0042db75:
        mov edx,dword ptr [eax]
    L_0042db77:
        cmp word ptr [edx+38Ah],cx
    L_0042db7e:
        je short L_0042dbc2
    L_0042db80:
        mov eax,dword ptr [eax+4]
    L_0042db83:
        cmp eax,ebx
    L_0042db85:
        jne short L_0042db75
    L_0042db87:
        mov dword ptr [esp+14h],ebx
    L_0042db8b:
        push 2Dh
    L_0042db8d:
        lea eax,[esp+18h]
    L_0042db91:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042db96:
        xor esi,esi
    L_0042db98:
        mov si,word ptr [ebp+24h]
    L_0042db9c:
        add si,11h
    L_0042dba0:
        mov ecx,1
    L_0042dba5:
        mov eax,ebp
    L_0042dba7:
        call asm_FUN_0042c770_0042c770
    L_0042dbac:
        pop edi
    L_0042dbad:
        pop esi
    L_0042dbae:
        pop ebx
    L_0042dbaf:
        mov eax,1
    L_0042dbb4:
        pop ebp
    L_0042dbb5:
        ret 4
    L_0042dbb8:
        mov eax,dword ptr [eax]
    L_0042dbba:
        mov ecx,dword ptr [eax]
    L_0042dbbc:
        mov dword ptr [esp+14h],ecx
    L_0042dbc0:
        jmp short L_0042db46
    L_0042dbc2:
        mov eax,dword ptr [eax]
    L_0042dbc4:
        mov ecx,dword ptr [eax]
    L_0042dbc6:
        mov dword ptr [esp+14h],ecx
    L_0042dbca:
        jmp short L_0042db8b
    L_0042dbcc:
        mov edx,dword ptr [ebp+24h]
    L_0042dbcf:
        lea esi,[ebp+24h]
    L_0042dbd2:
        mov dword ptr [esi+4],edx
    L_0042dbd5:
        mov cl,byte ptr [data_00474e36]
    L_0042dbdb:
        mov al,10h
    L_0042dbdd:
        test cl,al
    L_0042dbdf:
        jne short L_0042dbe9
    L_0042dbe1:
        test byte ptr [data_00474e34],al
    L_0042dbe7:
        je short L_0042dbf2
    L_0042dbe9:
        push 0FFFFFFFFh
    L_0042dbeb:
        mov eax,esi
    L_0042dbed:
        call asm_MenuCursor_Advance_0044bea0
    L_0042dbf2:
        test byte ptr [data_00474e36],20h
    L_0042dbf9:
        jne short L_0042dc04
    L_0042dbfb:
        test byte ptr [data_00474e34],20h
    L_0042dc02:
        je short L_0042dc0d
    L_0042dc04:
        push 1
    L_0042dc06:
        mov eax,esi
    L_0042dc08:
        call asm_MenuCursor_Advance_0044bea0
    L_0042dc0d:
        mov eax,dword ptr [esi+4]
    L_0042dc10:
        mov ecx,dword ptr [esi]
    L_0042dc12:
        xor ebx,ebx
    L_0042dc14:
        cmp eax,ecx
    L_0042dc16:
        je short L_0042dc55
    L_0042dc18:
        push ebx
    L_0042dc19:
        mov edi,0Ch
    L_0042dc1e:
        mov ecx,492590h
    L_0042dc23:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042dc28:
        mov ecx,dword ptr [ebp+2C8h]
    L_0042dc2e:
        mov edx,dword ptr [data_00491c10]
    L_0042dc34:
        push ecx
    L_0042dc35:
        mov edi,3
    L_0042dc3a:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042dc3f:
        xor esi,esi
    L_0042dc41:
        mov si,word ptr [ebp+24h]
    L_0042dc45:
        add si,7
    L_0042dc49:
        mov ecx,1
    L_0042dc4e:
        mov eax,ebp
    L_0042dc50:
        call asm_FUN_0042c770_0042c770
    L_0042dc55:
        test byte ptr [data_00474e36],0Ah
    L_0042dc5c:
        mov eax,dword ptr [ebp+24h]
    L_0042dc5f:
        je short L_0042dccb
    L_0042dc61:
        cmp eax,5
    L_0042dc64:
        je asm_target_0042e27b
    L_0042dc6a:
        push ebx
    L_0042dc6b:
        mov edi,0Bh
    L_0042dc70:
        mov ecx,492590h
    L_0042dc75:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042dc7a:
        mov eax,dword ptr [ebp+2Ch]
    L_0042dc7d:
        cmp eax,ebx
    L_0042dc7f:
        je short L_0042dc96
    L_0042dc81:
        cmp eax,5
    L_0042dc84:
        jg short L_0042dc8c
    L_0042dc86:
        dec eax
    L_0042dc87:
        mov dword ptr [ebp+24h],eax
    L_0042dc8a:
        jmp short L_0042dc9d
    L_0042dc8c:
        mov eax,5
    L_0042dc91:
        mov dword ptr [ebp+24h],eax
    L_0042dc94:
        jmp short L_0042dc9d
    L_0042dc96:
        mov dword ptr [ebp+24h],5
    L_0042dc9d:
        mov ecx,1
    L_0042dca2:
        mov eax,ebp
    L_0042dca4:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_0042dca9:
        xor esi,esi
    L_0042dcab:
        mov si,word ptr [ebp+24h]
    L_0042dcaf:
        add si,7
    L_0042dcb3:
        mov ecx,1
    L_0042dcb8:
        mov eax,ebp
    L_0042dcba:
        call asm_FUN_0042c770_0042c770
    L_0042dcbf:
        pop edi
    L_0042dcc0:
        pop esi
    L_0042dcc1:
        pop ebx
    L_0042dcc2:
        mov eax,1
    L_0042dcc7:
        pop ebp
    L_0042dcc8:
        ret 4
    L_0042dccb:
        cmp eax,2
    L_0042dcce:
        jne short L_0042dcf1
    L_0042dcd0:
        push 3Ch
    L_0042dcd2:
        lea ecx,[ebp+2B0h]
    L_0042dcd8:
        call asm_AtInterval_FrameCounterPair_00427c70
    L_0042dcdd:
        test eax,eax
    L_0042dcdf:
        je short L_0042dcf1
    L_0042dce1:
        push ebx
    L_0042dce2:
        mov edi,4
    L_0042dce7:
        mov ecx,492590h
    L_0042dcec:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042dcf1:
        mov eax,40h
    L_0042dcf6:
        mov ecx,474E30h
    L_0042dcfb:
        call asm_InputMaskActive_0040ace0
    L_0042dd00:
        test ax,ax
    L_0042dd03:
        mov esi,dword ptr [data_00491c10]
    L_0042dd09:
        mov edi,1Fh
    L_0042dd0e:
        je asm_target_0042def6
    L_0042dd14:
        mov eax,dword ptr [ebp+24h]
    L_0042dd17:
        sub eax,ebx
    L_0042dd19:
        je short L_0042dd8b
    L_0042dd1b:
        dec eax
    L_0042dd1c:
        je short L_0042dd58
    L_0042dd1e:
        dec eax
    L_0042dd1f:
        jne asm_target_0042def6
    L_0042dd25:
        cmp byte ptr [data_00491d69],5
    L_0042dd2c:
        jge short L_0042dd40
    L_0042dd2e:
        mov edi,ebp
    L_0042dd30:
        mov byte ptr [data_00491d69],bl
    L_0042dd36:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042dd3b:
        jmp asm_target_0042def6
    L_0042dd40:
        mov al,byte ptr [data_00491d69]
    L_0042dd45:
        add al,0FBh
    L_0042dd47:
        mov edi,ebp
    L_0042dd49:
        mov byte ptr [data_00491d69],al
    L_0042dd4e:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042dd53:
        jmp asm_target_0042def6
    L_0042dd58:
        cmp byte ptr [data_00491d68],5
    L_0042dd5f:
        jge short L_0042dd73
    L_0042dd61:
        mov edi,ebp
    L_0042dd63:
        mov byte ptr [data_00491d68],bl
    L_0042dd69:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042dd6e:
        jmp asm_target_0042def6
    L_0042dd73:
        mov al,byte ptr [data_00491d68]
    L_0042dd78:
        add al,0FBh
    L_0042dd7a:
        mov edi,ebp
    L_0042dd7c:
        mov byte ptr [data_00491d68],al
    L_0042dd81:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042dd86:
        jmp asm_target_0042def6
    L_0042dd8b:
        mov al,byte ptr [data_00491d6a]
    L_0042dd90:
        cmp al,bl
    L_0042dd92:
        jbe asm_target_0042de42
    L_0042dd98:
        dec al
    L_0042dd9a:
        cmp al,bl
    L_0042dd9c:
        mov byte ptr [data_00491d6a],al
    L_0042dda1:
        jne asm_target_0042df66
    L_0042dda7:
        mov edx,dword ptr [ebp+2C8h]
    L_0042ddad:
        push edx
    L_0042ddae:
        mov edx,esi
    L_0042ddb0:
        call asm_AnimationManager_Find_004491c0
    L_0042ddb5:
        cmp eax,ebx
    L_0042ddb7:
        jne short L_0042ddbf
    L_0042ddb9:
        mov dword ptr [ebp+2C8h],ebx
    L_0042ddbf:
        add eax,10h
    L_0042ddc2:
        cmp eax,ebx
    L_0042ddc4:
        TH10_REL8(0x74, 0x0042ddc4, VA_asm_target_0042dde6)
    L_0042ddc6:
        TH10_REL8(0xeb, 0x0042ddc6, VA_asm_FUN_0042d920_part_0042ddd0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0042ddd0:
        mov ecx,dword ptr [eax]
    L_0042ddd2:
        cmp word ptr [ecx+38Ah],di
    L_0042ddd9:
        je asm_target_0042df4a
    L_0042dddf:
        mov eax,dword ptr [eax+4]
    L_0042dde2:
        cmp eax,ebx
    L_0042dde4:
        jne short L_0042ddd0
    L_0042dde6:
        mov dword ptr [esp+14h],ebx
    L_0042ddea:
        push 2Eh
    L_0042ddec:
        lea eax,[esp+18h]
    L_0042ddf0:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042ddf5:
        mov ecx,dword ptr [ebp+2C8h]
    L_0042ddfb:
        push ecx
    L_0042ddfc:
        mov edx,esi
    L_0042ddfe:
        call asm_AnimationManager_Find_004491c0
    L_0042de03:
        cmp eax,ebx
    L_0042de05:
        jne short L_0042de0d
    L_0042de07:
        mov dword ptr [ebp+2C8h],ebx
    L_0042de0d:
        add eax,10h
    L_0042de10:
        cmp eax,ebx
    L_0042de12:
        TH10_REL8(0x74, 0x0042de12, VA_asm_target_0042de37)
    L_0042de14:
        TH10_REL8(0xeb, 0x0042de14, VA_asm_FUN_0042d920_part_0042de20)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042de20:
        mov edx,dword ptr [eax]
    L_0042de22:
        cmp word ptr [edx+38Ah],20h
    L_0042de2a:
        je asm_target_0042df57
    L_0042de30:
        mov eax,dword ptr [eax+4]
    L_0042de33:
        cmp eax,ebx
    L_0042de35:
        jne short L_0042de20
    L_0042de37:
        mov dword ptr [esp+14h],ebx
    L_0042de3b:
        push 2Fh
    L_0042de3d:
        jmp asm_target_0042dedd
    L_0042de42:
        mov byte ptr [data_00491d6a],2
    L_0042de49:
        mov edx,dword ptr [ebp+2C8h]
    L_0042de4f:
        push edx
    L_0042de50:
        mov edx,esi
    L_0042de52:
        call asm_AnimationManager_Find_004491c0
    L_0042de57:
        cmp eax,ebx
    L_0042de59:
        jne short L_0042de61
    L_0042de5b:
        mov dword ptr [ebp+2C8h],ebx
    L_0042de61:
        add eax,10h
    L_0042de64:
        cmp eax,ebx
    L_0042de66:
        TH10_REL8(0x74, 0x0042de66, VA_asm_target_0042de86)
    L_0042de68:
        TH10_REL8(0xeb, 0x0042de68, VA_asm_FUN_0042d920_part_0042de70)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042de70:
        mov ecx,dword ptr [eax]
    L_0042de72:
        cmp word ptr [ecx+38Ah],di
    L_0042de79:
        je asm_target_0042e007
    L_0042de7f:
        mov eax,dword ptr [eax+4]
    L_0042de82:
        cmp eax,ebx
    L_0042de84:
        jne short L_0042de70
    L_0042de86:
        mov dword ptr [esp+14h],ebx
    L_0042de8a:
        push 2Ch
    L_0042de8c:
        lea eax,[esp+18h]
    L_0042de90:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042de95:
        mov ecx,dword ptr [ebp+2C8h]
    L_0042de9b:
        push ecx
    L_0042de9c:
        mov edx,esi
    L_0042de9e:
        call asm_AnimationManager_Find_004491c0
    L_0042dea3:
        cmp eax,ebx
    L_0042dea5:
        jne short L_0042dead
    L_0042dea7:
        mov dword ptr [ebp+2C8h],ebx
    L_0042dead:
        add eax,10h
    L_0042deb0:
        cmp eax,ebx
    L_0042deb2:
        TH10_REL8(0x74, 0x0042deb2, VA_asm_target_0042ded7)
    L_0042deb4:
        TH10_REL8(0xeb, 0x0042deb4, VA_asm_FUN_0042d920_part_0042dec0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042dec0:
        mov edx,dword ptr [eax]
    L_0042dec2:
        cmp word ptr [edx+38Ah],20h
    L_0042deca:
        je asm_target_0042e014
    L_0042ded0:
        mov eax,dword ptr [eax+4]
    L_0042ded3:
        cmp eax,ebx
    L_0042ded5:
        jne short L_0042dec0
    L_0042ded7:
        mov dword ptr [esp+14h],ebx
    L_0042dedb:
        push 2Dh
    L_0042dedd:
        lea eax,[esp+18h]
    L_0042dee1:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042dee6:
        push ebx
    L_0042dee7:
        mov edi,0Ch
    L_0042deec:
        mov ecx,492590h
    L_0042def1:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042def6:
        mov eax,80h
    L_0042defb:
        mov ecx,474E30h
    L_0042df00:
        call asm_InputMaskActive_0040ace0
    L_0042df05:
        test ax,ax
    L_0042df08:
        je asm_target_0042e255
    L_0042df0e:
        mov eax,dword ptr [ebp+24h]
    L_0042df11:
        sub eax,ebx
    L_0042df13:
        je asm_target_0042e044
    L_0042df19:
        dec eax
    L_0042df1a:
        je asm_target_0042e021
    L_0042df20:
        dec eax
    L_0042df21:
        jne asm_target_0042e255
    L_0042df27:
        mov al,byte ptr [data_00491d69]
    L_0042df2c:
        add al,5
    L_0042df2e:
        cmp al,64h
    L_0042df30:
        mov byte ptr [data_00491d69],al
    L_0042df35:
        jle short L_0042df3e
    L_0042df37:
        mov byte ptr [data_00491d69],64h
    L_0042df3e:
        mov edi,ebp
    L_0042df40:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042df45:
        jmp asm_target_0042e255
    L_0042df4a:
        mov edx,dword ptr [eax]
    L_0042df4c:
        mov eax,dword ptr [edx]
    L_0042df4e:
        mov dword ptr [esp+14h],eax
    L_0042df52:
        jmp asm_target_0042ddea
    L_0042df57:
        mov eax,dword ptr [eax]
    L_0042df59:
        mov ecx,dword ptr [eax]
    L_0042df5b:
        mov dword ptr [esp+14h],ecx
    L_0042df5f:
        push 2Fh
    L_0042df61:
        jmp asm_target_0042dedd
    L_0042df66:
        cmp al,1
    L_0042df68:
        jne asm_target_0042de49
    L_0042df6e:
        mov edx,dword ptr [ebp+2C8h]
    L_0042df74:
        push edx
    L_0042df75:
        mov edx,esi
    L_0042df77:
        call asm_AnimationManager_Find_004491c0
    L_0042df7c:
        cmp eax,ebx
    L_0042df7e:
        jne short L_0042df86
    L_0042df80:
        mov dword ptr [ebp+2C8h],ebx
    L_0042df86:
        add eax,10h
    L_0042df89:
        cmp eax,ebx
    L_0042df8b:
        je short L_0042dfa2
    L_0042df8d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0042df90:
        mov ecx,dword ptr [eax]
    L_0042df92:
        cmp word ptr [ecx+38Ah],di
    L_0042df99:
        je short L_0042dfee
    L_0042df9b:
        mov eax,dword ptr [eax+4]
    L_0042df9e:
        cmp eax,ebx
    L_0042dfa0:
        jne short L_0042df90
    L_0042dfa2:
        mov dword ptr [esp+14h],ebx
    L_0042dfa6:
        push 30h
    L_0042dfa8:
        lea eax,[esp+18h]
    L_0042dfac:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042dfb1:
        mov ecx,dword ptr [ebp+2C8h]
    L_0042dfb7:
        push ecx
    L_0042dfb8:
        mov edx,esi
    L_0042dfba:
        call asm_AnimationManager_Find_004491c0
    L_0042dfbf:
        cmp eax,ebx
    L_0042dfc1:
        jne short L_0042dfc9
    L_0042dfc3:
        mov dword ptr [ebp+2C8h],ebx
    L_0042dfc9:
        add eax,10h
    L_0042dfcc:
        cmp eax,ebx
    L_0042dfce:
        je short L_0042dfe3
    L_0042dfd0:
        mov edx,dword ptr [eax]
    L_0042dfd2:
        cmp word ptr [edx+38Ah],20h
    L_0042dfda:
        je short L_0042dff8
    L_0042dfdc:
        mov eax,dword ptr [eax+4]
    L_0042dfdf:
        cmp eax,ebx
    L_0042dfe1:
        jne short L_0042dfd0
    L_0042dfe3:
        mov dword ptr [esp+14h],ebx
    L_0042dfe7:
        push 31h
    L_0042dfe9:
        jmp asm_target_0042dedd
    L_0042dfee:
        mov edx,dword ptr [eax]
    L_0042dff0:
        mov eax,dword ptr [edx]
    L_0042dff2:
        mov dword ptr [esp+14h],eax
    L_0042dff6:
        jmp short L_0042dfa6
    L_0042dff8:
        mov eax,dword ptr [eax]
    L_0042dffa:
        mov ecx,dword ptr [eax]
    L_0042dffc:
        mov dword ptr [esp+14h],ecx
    L_0042e000:
        push 31h
    L_0042e002:
        jmp asm_target_0042dedd
    L_0042e007:
        mov edx,dword ptr [eax]
    L_0042e009:
        mov eax,dword ptr [edx]
    L_0042e00b:
        mov dword ptr [esp+14h],eax
    L_0042e00f:
        jmp asm_target_0042de8a
    L_0042e014:
        mov eax,dword ptr [eax]
    L_0042e016:
        mov ecx,dword ptr [eax]
    L_0042e018:
        mov dword ptr [esp+14h],ecx
    L_0042e01c:
        jmp asm_target_0042dedb
    L_0042e021:
        mov al,byte ptr [data_00491d68]
    L_0042e026:
        add al,5
    L_0042e028:
        cmp al,64h
    L_0042e02a:
        mov byte ptr [data_00491d68],al
    L_0042e02f:
        jle short L_0042e038
    L_0042e031:
        mov byte ptr [data_00491d68],64h
    L_0042e038:
        mov edi,ebp
    L_0042e03a:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042e03f:
        jmp asm_target_0042e255
    L_0042e044:
        mov al,byte ptr [data_00491d6a]
    L_0042e049:
        cmp al,2
    L_0042e04b:
        jae short L_0042e056
    L_0042e04d:
        inc al
    L_0042e04f:
        mov byte ptr [data_00491d6a],al
    L_0042e054:
        jmp short L_0042e05c
    L_0042e056:
        mov byte ptr [data_00491d6a],bl
    L_0042e05c:
        push ebx
    L_0042e05d:
        mov edi,0Ch
    L_0042e062:
        mov ecx,492590h
    L_0042e067:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042e06c:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e072:
        mov al,byte ptr [data_00491d6a]
    L_0042e077:
        cmp al,bl
    L_0042e079:
        push edx
    L_0042e07a:
        mov edx,esi
    L_0042e07c:
        jne asm_target_0042e11b
    L_0042e082:
        call asm_AnimationManager_Find_004491c0
    L_0042e087:
        cmp eax,ebx
    L_0042e089:
        jne short L_0042e091
    L_0042e08b:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e091:
        add eax,10h
    L_0042e094:
        cmp eax,ebx
    L_0042e096:
        je short L_0042e0b2
    L_0042e098:
        mov ecx,1Fh
    L_0042e09d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0042e0a0:
        mov edx,dword ptr [eax]
    L_0042e0a2:
        cmp word ptr [edx+38Ah],cx
    L_0042e0a9:
        je short L_0042e102
    L_0042e0ab:
        mov eax,dword ptr [eax+4]
    L_0042e0ae:
        cmp eax,ebx
    L_0042e0b0:
        jne short L_0042e0a0
    L_0042e0b2:
        mov dword ptr [esp+14h],ebx
    L_0042e0b6:
        push 2Eh
    L_0042e0b8:
        lea eax,[esp+18h]
    L_0042e0bc:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e0c1:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e0c7:
        push edx
    L_0042e0c8:
        mov edx,esi
    L_0042e0ca:
        call asm_AnimationManager_Find_004491c0
    L_0042e0cf:
        cmp eax,ebx
    L_0042e0d1:
        jne short L_0042e0d9
    L_0042e0d3:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e0d9:
        add eax,10h
    L_0042e0dc:
        cmp eax,ebx
    L_0042e0de:
        je short L_0042e0f7
    L_0042e0e0:
        mov ecx,20h
    L_0042e0e5:
        mov edx,dword ptr [eax]
    L_0042e0e7:
        cmp word ptr [edx+38Ah],cx
    L_0042e0ee:
        je short L_0042e10c
    L_0042e0f0:
        mov eax,dword ptr [eax+4]
    L_0042e0f3:
        cmp eax,ebx
    L_0042e0f5:
        jne short L_0042e0e5
    L_0042e0f7:
        mov dword ptr [esp+14h],ebx
    L_0042e0fb:
        push 2Fh
    L_0042e0fd:
        jmp asm_target_0042e24c
    L_0042e102:
        mov eax,dword ptr [eax]
    L_0042e104:
        mov ecx,dword ptr [eax]
    L_0042e106:
        mov dword ptr [esp+14h],ecx
    L_0042e10a:
        jmp short L_0042e0b6
    L_0042e10c:
        mov eax,dword ptr [eax]
    L_0042e10e:
        mov ecx,dword ptr [eax]
    L_0042e110:
        mov dword ptr [esp+14h],ecx
    L_0042e114:
        push 2Fh
    L_0042e116:
        jmp asm_target_0042e24c
    L_0042e11b:
        cmp al,1
    L_0042e11d:
        jne asm_target_0042e1bb
    L_0042e123:
        call asm_AnimationManager_Find_004491c0
    L_0042e128:
        cmp eax,ebx
    L_0042e12a:
        jne short L_0042e132
    L_0042e12c:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e132:
        add eax,10h
    L_0042e135:
        cmp eax,ebx
    L_0042e137:
        je short L_0042e152
    L_0042e139:
        mov ecx,1Fh
    L_0042e13e:
        mov edi,edi
    L_0042e140:
        mov edx,dword ptr [eax]
    L_0042e142:
        cmp word ptr [edx+38Ah],cx
    L_0042e149:
        je short L_0042e1a2
    L_0042e14b:
        mov eax,dword ptr [eax+4]
    L_0042e14e:
        cmp eax,ebx
    L_0042e150:
        jne short L_0042e140
    L_0042e152:
        mov dword ptr [esp+14h],ebx
    L_0042e156:
        push 30h
    L_0042e158:
        lea eax,[esp+18h]
    L_0042e15c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e161:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e167:
        push edx
    L_0042e168:
        mov edx,esi
    L_0042e16a:
        call asm_AnimationManager_Find_004491c0
    L_0042e16f:
        cmp eax,ebx
    L_0042e171:
        jne short L_0042e179
    L_0042e173:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e179:
        add eax,10h
    L_0042e17c:
        cmp eax,ebx
    L_0042e17e:
        je short L_0042e197
    L_0042e180:
        mov ecx,20h
    L_0042e185:
        mov edx,dword ptr [eax]
    L_0042e187:
        cmp word ptr [edx+38Ah],cx
    L_0042e18e:
        je short L_0042e1ac
    L_0042e190:
        mov eax,dword ptr [eax+4]
    L_0042e193:
        cmp eax,ebx
    L_0042e195:
        jne short L_0042e185
    L_0042e197:
        mov dword ptr [esp+14h],ebx
    L_0042e19b:
        push 31h
    L_0042e19d:
        jmp asm_target_0042e24c
    L_0042e1a2:
        mov eax,dword ptr [eax]
    L_0042e1a4:
        mov ecx,dword ptr [eax]
    L_0042e1a6:
        mov dword ptr [esp+14h],ecx
    L_0042e1aa:
        jmp short L_0042e156
    L_0042e1ac:
        mov eax,dword ptr [eax]
    L_0042e1ae:
        mov ecx,dword ptr [eax]
    L_0042e1b0:
        mov dword ptr [esp+14h],ecx
    L_0042e1b4:
        push 31h
    L_0042e1b6:
        jmp asm_target_0042e24c
    L_0042e1bb:
        call asm_AnimationManager_Find_004491c0
    L_0042e1c0:
        cmp eax,ebx
    L_0042e1c2:
        jne short L_0042e1ca
    L_0042e1c4:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e1ca:
        add eax,10h
    L_0042e1cd:
        cmp eax,ebx
    L_0042e1cf:
        TH10_REL8(0x74, 0x0042e1cf, VA_asm_target_0042e1f6)
    L_0042e1d1:
        mov ecx,1Fh
    L_0042e1d6:
        TH10_REL8(0xeb, 0x0042e1d6, VA_asm_FUN_0042d920_part_0042e1e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0042e1e0:
        mov edx,dword ptr [eax]
    L_0042e1e2:
        cmp word ptr [edx+38Ah],cx
    L_0042e1e9:
        je asm_target_0042e2b4
    L_0042e1ef:
        mov eax,dword ptr [eax+4]
    L_0042e1f2:
        cmp eax,ebx
    L_0042e1f4:
        jne short L_0042e1e0
    L_0042e1f6:
        mov dword ptr [esp+14h],ebx
    L_0042e1fa:
        push 2Ch
    L_0042e1fc:
        lea eax,[esp+18h]
    L_0042e200:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e205:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e20b:
        push edx
    L_0042e20c:
        mov edx,esi
    L_0042e20e:
        call asm_AnimationManager_Find_004491c0
    L_0042e213:
        cmp eax,ebx
    L_0042e215:
        jne short L_0042e21d
    L_0042e217:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e21d:
        add eax,10h
    L_0042e220:
        cmp eax,ebx
    L_0042e222:
        je short L_0042e246
    L_0042e224:
        mov ecx,20h
    L_0042e229:
        lea esp,[esp+force_disp32_zero]
    L_0042e230:
        mov edx,dword ptr [eax]
    L_0042e232:
        cmp word ptr [edx+38Ah],cx
    L_0042e239:
        je asm_target_0042e2c1
    L_0042e23f:
        mov eax,dword ptr [eax+4]
    L_0042e242:
        cmp eax,ebx
    L_0042e244:
        jne short L_0042e230
    L_0042e246:
        mov dword ptr [esp+14h],ebx
    L_0042e24a:
        push 2Dh
    L_0042e24c:
        lea eax,[esp+18h]
    L_0042e250:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e255:
        test dword ptr [data_00474e36],1001h
    L_0042e25f:
        je asm_target_0042e574
    L_0042e265:
        mov eax,dword ptr [ebp+24h]
    L_0042e268:
        sub eax,3
    L_0042e26b:
        je asm_target_0042e4f6
    L_0042e271:
        dec eax
    L_0042e272:
        je short L_0042e2ce
    L_0042e274:
        dec eax
    L_0042e275:
        jne asm_target_0042e574
    L_0042e27b:
        mov esi,6
    L_0042e280:
        mov ecx,1
    L_0042e285:
        mov eax,ebp
    L_0042e287:
        call asm_FUN_0042c770_0042c770
    L_0042e28c:
        mov edi,0Bh
    L_0042e291:
        push ebx
    L_0042e292:
        mov ecx,492590h
    L_0042e297:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042e29c:
        mov ecx,4
    L_0042e2a1:
        mov eax,ebp
    L_0042e2a3:
        call asm_GameState_SetTimerTarget_0042c620
    L_0042e2a8:
        pop edi
    L_0042e2a9:
        pop esi
    L_0042e2aa:
        pop ebx
    L_0042e2ab:
        mov eax,1
    L_0042e2b0:
        pop ebp
    L_0042e2b1:
        ret 4
    L_0042e2b4:
        mov eax,dword ptr [eax]
    L_0042e2b6:
        mov ecx,dword ptr [eax]
    L_0042e2b8:
        mov dword ptr [esp+14h],ecx
    L_0042e2bc:
        jmp asm_target_0042e1fa
    L_0042e2c1:
        mov eax,dword ptr [eax]
    L_0042e2c3:
        mov ecx,dword ptr [eax]
    L_0042e2c5:
        mov dword ptr [esp+14h],ecx
    L_0042e2c9:
        jmp asm_target_0042e24a
    L_0042e2ce:
        mov edi,ebp
    L_0042e2d0:
        mov byte ptr [data_00491d68],64h
    L_0042e2d7:
        mov byte ptr [data_00491d69],50h
    L_0042e2de:
        mov byte ptr [data_00491d6a],bl
    L_0042e2e4:
        call asm_FUN_0042e5a0_0042e5a0
    L_0042e2e9:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e2ef:
        mov al,byte ptr [data_00491d6a]
    L_0042e2f4:
        cmp al,bl
    L_0042e2f6:
        push edx
    L_0042e2f7:
        mov edx,esi
    L_0042e2f9:
        jne asm_target_0042e39b
    L_0042e2ff:
        call asm_AnimationManager_Find_004491c0
    L_0042e304:
        cmp eax,ebx
    L_0042e306:
        jne short L_0042e30e
    L_0042e308:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e30e:
        add eax,10h
    L_0042e311:
        cmp eax,ebx
    L_0042e313:
        je short L_0042e332
    L_0042e315:
        mov ecx,1Fh
    L_0042e31a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042e320:
        mov edx,dword ptr [eax]
    L_0042e322:
        cmp word ptr [edx+38Ah],cx
    L_0042e329:
        je short L_0042e382
    L_0042e32b:
        mov eax,dword ptr [eax+4]
    L_0042e32e:
        cmp eax,ebx
    L_0042e330:
        jne short L_0042e320
    L_0042e332:
        mov dword ptr [esp+14h],ebx
    L_0042e336:
        push 2Eh
    L_0042e338:
        lea eax,[esp+18h]
    L_0042e33c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e341:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e347:
        push edx
    L_0042e348:
        mov edx,esi
    L_0042e34a:
        call asm_AnimationManager_Find_004491c0
    L_0042e34f:
        cmp eax,ebx
    L_0042e351:
        jne short L_0042e359
    L_0042e353:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e359:
        add eax,10h
    L_0042e35c:
        cmp eax,ebx
    L_0042e35e:
        je short L_0042e377
    L_0042e360:
        mov ecx,20h
    L_0042e365:
        mov edx,dword ptr [eax]
    L_0042e367:
        cmp word ptr [edx+38Ah],cx
    L_0042e36e:
        je short L_0042e38c
    L_0042e370:
        mov eax,dword ptr [eax+4]
    L_0042e373:
        cmp eax,ebx
    L_0042e375:
        jne short L_0042e365
    L_0042e377:
        mov dword ptr [esp+14h],ebx
    L_0042e37b:
        push 2Fh
    L_0042e37d:
        jmp asm_target_0042e4bd
    L_0042e382:
        mov eax,dword ptr [eax]
    L_0042e384:
        mov ecx,dword ptr [eax]
    L_0042e386:
        mov dword ptr [esp+14h],ecx
    L_0042e38a:
        jmp short L_0042e336
    L_0042e38c:
        mov eax,dword ptr [eax]
    L_0042e38e:
        mov ecx,dword ptr [eax]
    L_0042e390:
        mov dword ptr [esp+14h],ecx
    L_0042e394:
        push 2Fh
    L_0042e396:
        jmp asm_target_0042e4bd
    L_0042e39b:
        cmp al,1
    L_0042e39d:
        jne asm_target_0042e43b
    L_0042e3a3:
        call asm_AnimationManager_Find_004491c0
    L_0042e3a8:
        cmp eax,ebx
    L_0042e3aa:
        jne short L_0042e3b2
    L_0042e3ac:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e3b2:
        add eax,10h
    L_0042e3b5:
        cmp eax,ebx
    L_0042e3b7:
        je short L_0042e3d2
    L_0042e3b9:
        mov ecx,1Fh
    L_0042e3be:
        mov edi,edi
    L_0042e3c0:
        mov edx,dword ptr [eax]
    L_0042e3c2:
        cmp word ptr [edx+38Ah],cx
    L_0042e3c9:
        je short L_0042e422
    L_0042e3cb:
        mov eax,dword ptr [eax+4]
    L_0042e3ce:
        cmp eax,ebx
    L_0042e3d0:
        jne short L_0042e3c0
    L_0042e3d2:
        mov dword ptr [esp+14h],ebx
    L_0042e3d6:
        push 30h
    L_0042e3d8:
        lea eax,[esp+18h]
    L_0042e3dc:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e3e1:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e3e7:
        push edx
    L_0042e3e8:
        mov edx,esi
    L_0042e3ea:
        call asm_AnimationManager_Find_004491c0
    L_0042e3ef:
        cmp eax,ebx
    L_0042e3f1:
        jne short L_0042e3f9
    L_0042e3f3:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e3f9:
        add eax,10h
    L_0042e3fc:
        cmp eax,ebx
    L_0042e3fe:
        je short L_0042e417
    L_0042e400:
        mov ecx,20h
    L_0042e405:
        mov edx,dword ptr [eax]
    L_0042e407:
        cmp word ptr [edx+38Ah],cx
    L_0042e40e:
        je short L_0042e42c
    L_0042e410:
        mov eax,dword ptr [eax+4]
    L_0042e413:
        cmp eax,ebx
    L_0042e415:
        jne short L_0042e405
    L_0042e417:
        mov dword ptr [esp+14h],ebx
    L_0042e41b:
        push 31h
    L_0042e41d:
        jmp asm_target_0042e4bd
    L_0042e422:
        mov eax,dword ptr [eax]
    L_0042e424:
        mov ecx,dword ptr [eax]
    L_0042e426:
        mov dword ptr [esp+14h],ecx
    L_0042e42a:
        jmp short L_0042e3d6
    L_0042e42c:
        mov eax,dword ptr [eax]
    L_0042e42e:
        mov ecx,dword ptr [eax]
    L_0042e430:
        mov dword ptr [esp+14h],ecx
    L_0042e434:
        push 31h
    L_0042e436:
        jmp asm_target_0042e4bd
    L_0042e43b:
        call asm_AnimationManager_Find_004491c0
    L_0042e440:
        cmp eax,ebx
    L_0042e442:
        jne short L_0042e44a
    L_0042e444:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e44a:
        add eax,10h
    L_0042e44d:
        cmp eax,ebx
    L_0042e44f:
        TH10_REL8(0x74, 0x0042e44f, VA_asm_target_0042e472)
    L_0042e451:
        mov ecx,1Fh
    L_0042e456:
        TH10_REL8(0xeb, 0x0042e456, VA_asm_FUN_0042d920_part_0042e460)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0042e460:
        mov edx,dword ptr [eax]
    L_0042e462:
        cmp word ptr [edx+38Ah],cx
    L_0042e469:
        je short L_0042e4e2
    L_0042e46b:
        mov eax,dword ptr [eax+4]
    L_0042e46e:
        cmp eax,ebx
    L_0042e470:
        jne short L_0042e460
    L_0042e472:
        mov dword ptr [esp+14h],ebx
    L_0042e476:
        push 2Ch
    L_0042e478:
        lea eax,[esp+18h]
    L_0042e47c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e481:
        mov edx,dword ptr [ebp+2C8h]
    L_0042e487:
        push edx
    L_0042e488:
        mov edx,esi
    L_0042e48a:
        call asm_AnimationManager_Find_004491c0
    L_0042e48f:
        cmp eax,ebx
    L_0042e491:
        jne short L_0042e499
    L_0042e493:
        mov dword ptr [ebp+2C8h],ebx
    L_0042e499:
        add eax,10h
    L_0042e49c:
        cmp eax,ebx
    L_0042e49e:
        je short L_0042e4b7
    L_0042e4a0:
        mov ecx,20h
    L_0042e4a5:
        mov edx,dword ptr [eax]
    L_0042e4a7:
        cmp word ptr [edx+38Ah],cx
    L_0042e4ae:
        je short L_0042e4ec
    L_0042e4b0:
        mov eax,dword ptr [eax+4]
    L_0042e4b3:
        cmp eax,ebx
    L_0042e4b5:
        jne short L_0042e4a5
    L_0042e4b7:
        mov dword ptr [esp+14h],ebx
    L_0042e4bb:
        push 2Dh
    L_0042e4bd:
        lea eax,[esp+18h]
    L_0042e4c1:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_0042e4c6:
        push ebx
    L_0042e4c7:
        mov edi,0Ah
    L_0042e4cc:
        mov ecx,492590h
    L_0042e4d1:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042e4d6:
        pop edi
    L_0042e4d7:
        pop esi
    L_0042e4d8:
        pop ebx
    L_0042e4d9:
        mov eax,1
    L_0042e4de:
        pop ebp
    L_0042e4df:
        ret 4
    L_0042e4e2:
        mov eax,dword ptr [eax]
    L_0042e4e4:
        mov ecx,dword ptr [eax]
    L_0042e4e6:
        mov dword ptr [esp+14h],ecx
    L_0042e4ea:
        jmp short L_0042e476
    L_0042e4ec:
        mov eax,dword ptr [eax]
    L_0042e4ee:
        mov ecx,dword ptr [eax]
    L_0042e4f0:
        mov dword ptr [esp+14h],ecx
    L_0042e4f4:
        jmp short L_0042e4bb
    L_0042e4f6:
        mov esi,6
    L_0042e4fb:
        mov ecx,1
    L_0042e500:
        mov eax,ebp
    L_0042e502:
        call asm_FUN_0042c770_0042c770
    L_0042e507:
        mov edi,0Ah
    L_0042e50c:
        jmp asm_target_0042e291
    L_0042e511:
        cmp dword ptr [ebp+2B4h],0Ah
    L_0042e518:
        jl short L_0042e574
    L_0042e51a:
        mov eax,dword ptr [ebp+24h]
    L_0042e51d:
        sub eax,3
    L_0042e520:
        lea esi,[ebp+24h]
    L_0042e523:
        je short L_0042e561
    L_0042e525:
        sub eax,2
    L_0042e528:
        jne short L_0042e574
    L_0042e52a:
        mov ecx,5Ah
    L_0042e52f:
        mov eax,ebp
    L_0042e531:
        call asm_GameState_DispatchAnimationSlot_0042c730
    L_0042e536:
        mov ecx,5Bh
    L_0042e53b:
        mov eax,ebp
    L_0042e53d:
        call asm_GameState_DispatchAnimationSlot_0042c730
    L_0042e542:
        mov ecx,2
    L_0042e547:
        mov eax,ebp
    L_0042e549:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042e54e:
        mov eax,esi
    L_0042e550:
        call asm_Score_InputHistoryStep_0044be70
    L_0042e555:
        pop edi
    L_0042e556:
        pop esi
    L_0042e557:
        pop ebx
    L_0042e558:
        mov eax,1
    L_0042e55d:
        pop ebp
    L_0042e55e:
        ret 4
    L_0042e561:
        mov ecx,5
    L_0042e566:
        mov eax,ebp
    L_0042e568:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_0042e56d:
        mov eax,esi
    L_0042e56f:
        call asm_Score_InputHistorySave_0044be20
    L_0042e574:
        pop edi
    L_0042e575:
        pop esi
    L_0042e576:
        pop ebx
    L_0042e577:
        mov eax,1
    L_0042e57c:
        pop ebp
    L_0042e57d:
        ret 4
        _emit 0x42
        _emit 0xd9
        _emit 0x42
        _emit 0x00
        _emit 0x7b
        _emit 0xd9
        _emit 0x42
        _emit 0x00
        _emit 0xcc
        _emit 0xdb
        _emit 0x42
        _emit 0x00
        _emit 0x74
        _emit 0xe5
        _emit 0x42
        _emit 0x00
        _emit 0x11
        _emit 0xe5
        _emit 0x42
        _emit 0x00
    }
}
