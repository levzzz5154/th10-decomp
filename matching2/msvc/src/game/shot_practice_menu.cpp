#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00430A60..0x00430FDA: FUN_00430a60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00430a60_00430a60() {
    __asm {
    L_00430a60:
        push ebp
    L_00430a61:
        mov ebp,dword ptr [esp+8]
    L_00430a65:
        mov eax,dword ptr [ebp+20h]
    L_00430a68:
        cmp eax,4
    L_00430a6b:
        ja asm_target_00430fd2
    L_00430a71:
        push ebx
    L_00430a72:
        push esi
    L_00430a73:
        push edi
    L_00430a74:
        jmp dword ptr [eax*4+430FDCh]
    L_00430a7b:
        mov dword ptr [ebp+2Ch],3
    L_00430a82:
        cmp dword ptr [data_00474c74],4
    L_00430a89:
        jne asm_target_00430bfc
    L_00430a8f:
        mov eax,dword ptr [data_00474c68]
    L_00430a94:
        mov ecx,dword ptr [data_0047783c]
    L_00430a9a:
        lea esi,[ecx+eax*2]
    L_00430a9d:
        mov bl,byte ptr [eax+esi+1D888h]
    L_00430aa4:
        xor edx,edx
    L_00430aa6:
        cmp bl,dl
    L_00430aa8:
        jne short L_00430b1c
    L_00430aaa:
        cmp dword ptr [ebp+24h],edx
    L_00430aad:
        jne short L_00430b04
    L_00430aaf:
        lea esi,[ecx+eax*2+13B06h]
    L_00430ab6:
        cmp byte ptr [eax+esi+9D83h],dl
    L_00430abd:
        mov eax,dword ptr [ebp+2Ch]
    L_00430ac0:
        je short L_00430ae4
    L_00430ac2:
        cmp eax,edx
    L_00430ac4:
        je short L_00430adb
    L_00430ac6:
        cmp eax,1
    L_00430ac9:
        jg short L_00430ad1
    L_00430acb:
        dec eax
    L_00430acc:
        mov dword ptr [ebp+24h],eax
    L_00430acf:
        jmp short L_00430b04
    L_00430ad1:
        mov eax,1
    L_00430ad6:
        mov dword ptr [ebp+24h],eax
    L_00430ad9:
        jmp short L_00430b04
    L_00430adb:
        mov dword ptr [ebp+24h],1
    L_00430ae2:
        jmp short L_00430b04
    L_00430ae4:
        cmp eax,edx
    L_00430ae6:
        je short L_00430afd
    L_00430ae8:
        cmp eax,2
    L_00430aeb:
        jg short L_00430af3
    L_00430aed:
        dec eax
    L_00430aee:
        mov dword ptr [ebp+24h],eax
    L_00430af1:
        jmp short L_00430b04
    L_00430af3:
        mov eax,2
    L_00430af8:
        mov dword ptr [ebp+24h],eax
    L_00430afb:
        jmp short L_00430b04
    L_00430afd:
        mov dword ptr [ebp+24h],2
    L_00430b04:
        mov eax,dword ptr [ebp+0F8h]
    L_00430b0a:
        mov dword ptr [ebp+eax*4+0B4h],edx
    L_00430b11:
        inc dword ptr [ebp+0F8h]
    L_00430b17:
        mov eax,dword ptr [data_00474c68]
    L_00430b1c:
        lea esi,[ecx+eax*2+13B06h]
    L_00430b23:
        cmp byte ptr [eax+esi+9D83h],dl
    L_00430b2a:
        mov esi,1
    L_00430b2f:
        jne short L_00430b95
    L_00430b31:
        cmp dword ptr [ebp+24h],esi
    L_00430b34:
        jne short L_00430b7d
    L_00430b36:
        lea edi,[ecx+eax*2]
    L_00430b39:
        cmp byte ptr [eax+edi+1D888h],dl
    L_00430b40:
        mov eax,dword ptr [ebp+2Ch]
    L_00430b43:
        je short L_00430b5d
    L_00430b45:
        cmp eax,edx
    L_00430b47:
        je short L_00430b58
    L_00430b49:
        jg short L_00430b51
    L_00430b4b:
        dec eax
    L_00430b4c:
        mov dword ptr [ebp+24h],eax
    L_00430b4f:
        jmp short L_00430b7d
    L_00430b51:
        xor eax,eax
    L_00430b53:
        mov dword ptr [ebp+24h],eax
    L_00430b56:
        jmp short L_00430b7d
    L_00430b58:
        mov dword ptr [ebp+24h],edx
    L_00430b5b:
        jmp short L_00430b7d
    L_00430b5d:
        cmp eax,edx
    L_00430b5f:
        je short L_00430b76
    L_00430b61:
        cmp eax,2
    L_00430b64:
        jg short L_00430b6c
    L_00430b66:
        dec eax
    L_00430b67:
        mov dword ptr [ebp+24h],eax
    L_00430b6a:
        jmp short L_00430b7d
    L_00430b6c:
        mov eax,2
    L_00430b71:
        mov dword ptr [ebp+24h],eax
    L_00430b74:
        jmp short L_00430b7d
    L_00430b76:
        mov dword ptr [ebp+24h],2
    L_00430b7d:
        mov eax,dword ptr [ebp+0F8h]
    L_00430b83:
        mov dword ptr [ebp+eax*4+0B4h],esi
    L_00430b8a:
        inc dword ptr [ebp+0F8h]
    L_00430b90:
        mov eax,dword ptr [data_00474c68]
    L_00430b95:
        lea ecx,[ecx+eax*2]
    L_00430b98:
        add eax,ecx
    L_00430b9a:
        cmp byte ptr [eax+1D88Ah],dl
    L_00430ba0:
        jne short L_00430bfc
    L_00430ba2:
        mov edi,dword ptr [ebp+24h]
    L_00430ba5:
        mov ecx,2
    L_00430baa:
        cmp edi,ecx
    L_00430bac:
        jne short L_00430be9
    L_00430bae:
        cmp byte ptr [eax+1D888h],dl
    L_00430bb4:
        mov eax,dword ptr [ebp+2Ch]
    L_00430bb7:
        je short L_00430bd1
    L_00430bb9:
        cmp eax,edx
    L_00430bbb:
        je short L_00430bcc
    L_00430bbd:
        jg short L_00430bc5
    L_00430bbf:
        dec eax
    L_00430bc0:
        mov dword ptr [ebp+24h],eax
    L_00430bc3:
        jmp short L_00430be9
    L_00430bc5:
        xor eax,eax
    L_00430bc7:
        mov dword ptr [ebp+24h],eax
    L_00430bca:
        jmp short L_00430be9
    L_00430bcc:
        mov dword ptr [ebp+24h],edx
    L_00430bcf:
        jmp short L_00430be9
    L_00430bd1:
        cmp eax,edx
    L_00430bd3:
        je short L_00430be6
    L_00430bd5:
        cmp eax,esi
    L_00430bd7:
        jg short L_00430bdf
    L_00430bd9:
        dec eax
    L_00430bda:
        mov dword ptr [ebp+24h],eax
    L_00430bdd:
        jmp short L_00430be9
    L_00430bdf:
        mov eax,esi
    L_00430be1:
        mov dword ptr [ebp+24h],eax
    L_00430be4:
        jmp short L_00430be9
    L_00430be6:
        mov dword ptr [ebp+24h],esi
    L_00430be9:
        mov edx,dword ptr [ebp+0F8h]
    L_00430bef:
        mov dword ptr [ebp+edx*4+0B4h],ecx
    L_00430bf6:
        inc dword ptr [ebp+0F8h]
    L_00430bfc:
        push ebp
    L_00430bfd:
        mov edi,64h
    L_00430c02:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00430c07:
        mov esi,dword ptr [data_00474c68]
    L_00430c0d:
        add esi,96h
    L_00430c13:
        mov edi,ebp
    L_00430c15:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430c1a:
        mov edi,dword ptr [data_00474c68]
    L_00430c20:
        add edi,96h
    L_00430c26:
        push ebp
    L_00430c27:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00430c2c:
        mov eax,dword ptr [data_00474c68]
    L_00430c31:
        mov ecx,dword ptr [ebp+eax*4+51Ch]
    L_00430c38:
        mov edx,dword ptr [data_00491c10]
    L_00430c3e:
        push ecx
    L_00430c3f:
        mov edi,3
    L_00430c44:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_00430c49:
        mov ecx,dword ptr [data_00474c68]
    L_00430c4f:
        xor esi,esi
    L_00430c51:
        mov si,word ptr [ebp+24h]
    L_00430c55:
        add si,11h
    L_00430c59:
        add ecx,96h
    L_00430c5f:
        mov eax,ebp
    L_00430c61:
        call asm_FUN_0042c770_0042c770
    L_00430c66:
        mov ecx,1
    L_00430c6b:
        mov eax,ebp
    L_00430c6d:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430c72:
        mov eax,dword ptr [data_00474c68]
    L_00430c77:
        mov edi,dword ptr [data_00474c74]
    L_00430c7d:
        mov ecx,dword ptr [data_0047783c]
    L_00430c83:
        mov edx,eax
    L_00430c85:
        imul edx,329Dh
    L_00430c8b:
        add edx,edi
    L_00430c8d:
        mov esi,dword ptr [ecx+edx*4+4D0h]
    L_00430c94:
        test esi,esi
    L_00430c96:
        jne short L_00430cbb
    L_00430c98:
        lea ebx,[eax+eax*2+8Ah]
    L_00430c9f:
        lea esi,[ebp+eax*4+51Ch]
    L_00430ca6:
        lea edi,[esp+14h]
    L_00430caa:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430caf:
        mov eax,edi
    L_00430cb1:
        call asm_AnimationManager_ClearFlag_004495e0
    L_00430cb6:
        mov eax,dword ptr [data_00474c68]
    L_00430cbb:
        mov edi,dword ptr [data_00474c74]
    L_00430cc1:
        mov ecx,dword ptr [data_0047783c]
    L_00430cc7:
        mov edx,eax
    L_00430cc9:
        imul edx,329Dh
    L_00430ccf:
        add edx,edi
    L_00430cd1:
        mov esi,dword ptr [ecx+edx*4+484Ch]
    L_00430cd8:
        test esi,esi
    L_00430cda:
        jne short L_00430cff
    L_00430cdc:
        lea ebx,[eax+eax*2+8Bh]
    L_00430ce3:
        lea esi,[ebp+eax*4+51Ch]
    L_00430cea:
        lea edi,[esp+14h]
    L_00430cee:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430cf3:
        mov eax,edi
    L_00430cf5:
        call asm_AnimationManager_ClearFlag_004495e0
    L_00430cfa:
        mov eax,dword ptr [data_00474c68]
    L_00430cff:
        mov edi,dword ptr [data_00474c74]
    L_00430d05:
        mov ecx,dword ptr [data_0047783c]
    L_00430d0b:
        mov edx,eax
    L_00430d0d:
        imul edx,329Dh
    L_00430d13:
        add edx,edi
    L_00430d15:
        mov esi,dword ptr [ecx+edx*4+8BC8h]
    L_00430d1c:
        test esi,esi
    L_00430d1e:
        jne short L_00430d3e
    L_00430d20:
        lea ebx,[eax+eax*2+8Ch]
    L_00430d27:
        lea esi,[ebp+eax*4+51Ch]
    L_00430d2e:
        lea edi,[esp+14h]
    L_00430d32:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430d37:
        mov eax,edi
    L_00430d39:
        call asm_AnimationManager_ClearFlag_004495e0
    L_00430d3e:
        cmp dword ptr [ebp+2B4h],6
    L_00430d45:
        jle asm_target_00430fcf
    L_00430d4b:
        mov ecx,2
    L_00430d50:
        mov eax,ebp
    L_00430d52:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430d57:
        pop edi
    L_00430d58:
        pop esi
    L_00430d59:
        pop ebx
    L_00430d5a:
        mov eax,1
    L_00430d5f:
        pop ebp
    L_00430d60:
        ret 4
    L_00430d63:
        mov edx,dword ptr [ebp+24h]
    L_00430d66:
        lea ebx,[ebp+24h]
    L_00430d69:
        mov dword ptr [ebx+4],edx
    L_00430d6c:
        mov cl,byte ptr [data_00474e36]
    L_00430d72:
        mov al,10h
    L_00430d74:
        test cl,al
    L_00430d76:
        jne short L_00430d80
    L_00430d78:
        test byte ptr [data_00474e34],al
    L_00430d7e:
        je short L_00430d89
    L_00430d80:
        push 0FFFFFFFFh
    L_00430d82:
        mov eax,ebx
    L_00430d84:
        call asm_MenuCursor_Advance_0044bea0
    L_00430d89:
        mov cl,byte ptr [data_00474e36]
    L_00430d8f:
        mov al,20h
    L_00430d91:
        test cl,al
    L_00430d93:
        jne short L_00430d9d
    L_00430d95:
        test byte ptr [data_00474e34],al
    L_00430d9b:
        je short L_00430da6
    L_00430d9d:
        push 1
    L_00430d9f:
        mov eax,ebx
    L_00430da1:
        call asm_MenuCursor_Advance_0044bea0
    L_00430da6:
        mov eax,dword ptr [ebx+4]
    L_00430da9:
        cmp eax,dword ptr [ebx]
    L_00430dab:
        je short L_00430ded
    L_00430dad:
        push 0
    L_00430daf:
        mov edi,0Ch
    L_00430db4:
        mov ecx,492590h
    L_00430db9:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430dbe:
        mov ecx,dword ptr [data_00474c68]
    L_00430dc4:
        add ecx,96h
    L_00430dca:
        mov eax,ebp
    L_00430dcc:
        call asm_GameState_DispatchAnimationSlotSecondary_0042c750
    L_00430dd1:
        mov ecx,dword ptr [data_00474c68]
    L_00430dd7:
        xor esi,esi
    L_00430dd9:
        mov si,word ptr [ebx]
    L_00430ddc:
        add si,7
    L_00430de0:
        add ecx,96h
    L_00430de6:
        mov eax,ebp
    L_00430de8:
        call asm_FUN_0042c770_0042c770
    L_00430ded:
        mov eax,dword ptr [data_00474e36]
    L_00430df2:
        test al,0Ah
    L_00430df4:
        je short L_00430e1f
    L_00430df6:
        mov ecx,4
    L_00430dfb:
        mov eax,ebp
    L_00430dfd:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430e02:
        push 0
    L_00430e04:
        mov edi,0Bh
    L_00430e09:
        mov ecx,492590h
    L_00430e0e:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430e13:
        pop edi
    L_00430e14:
        pop esi
    L_00430e15:
        pop ebx
    L_00430e16:
        mov eax,1
    L_00430e1b:
        pop ebp
    L_00430e1c:
        ret 4
    L_00430e1f:
        test eax,1001h
    L_00430e24:
        je asm_target_00430fcf
    L_00430e2a:
        mov ecx,3
    L_00430e2f:
        mov eax,ebp
    L_00430e31:
        call asm_GameState_SetTimerTarget_0042c620
    L_00430e36:
        push 0
    L_00430e38:
        mov edi,0Ah
    L_00430e3d:
        mov ecx,492590h
    L_00430e42:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430e47:
        mov eax,dword ptr [data_00474c68]
    L_00430e4c:
        mov edx,dword ptr [ebx]
    L_00430e4e:
        lea ecx,[eax+eax*2+3Fh]
    L_00430e52:
        lea ebx,[edx+ecx*2]
    L_00430e55:
        lea esi,[ebp+eax*4+51Ch]
    L_00430e5c:
        lea edi,[esp+14h]
    L_00430e60:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00430e65:
        mov esi,6
    L_00430e6a:
        mov eax,edi
    L_00430e6c:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00430e71:
        pop edi
    L_00430e72:
        pop esi
    L_00430e73:
        pop ebx
    L_00430e74:
        mov eax,1
    L_00430e79:
        pop ebp
    L_00430e7a:
        ret 4
    L_00430e7d:
        cmp dword ptr [ebp+2B4h],0Ah
    L_00430e84:
        jne short L_00430ee3
    L_00430e86:
        test byte ptr [data_00474ca0],10h
    L_00430e8d:
        jne short L_00430eba
    L_00430e8f:
        mov esi,dword ptr [data_004776e0]
    L_00430e95:
        push 43C40000h
    L_00430e9a:
        push 43F00000h
    L_00430e9f:
        call asm_FUN_0040c540_0040c540
    L_00430ea4:
        push 0
    L_00430ea6:
        push 0
    L_00430ea8:
        push 0
    L_00430eaa:
        push 20h
    L_00430eac:
        push 5
    L_00430eae:
        mov ebx,2Bh
    L_00430eb3:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00430eb8:
        jmp short L_00430ee3
    L_00430eba:
        mov ecx,dword ptr [ebp+24h]
    L_00430ebd:
        lea eax,[ebp+24h]
    L_00430ec0:
        mov dword ptr [data_00474c6c],ecx
    L_00430ec6:
        call asm_Score_InputHistorySave_0044be20
    L_00430ecb:
        mov esi,64h
    L_00430ed0:
        mov edi,ebp
    L_00430ed2:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430ed7:
        mov ecx,9
    L_00430edc:
        mov eax,ebp
    L_00430ede:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00430ee3:
        cmp dword ptr [ebp+2B4h],28h
    L_00430eea:
        jl asm_target_00430fcf
    L_00430ef0:
        mov edx,dword ptr [ebp+24h]
    L_00430ef3:
        lea eax,[ebp+24h]
    L_00430ef6:
        mov dword ptr [data_00474c6c],edx
    L_00430efc:
        call asm_Score_InputHistorySave_0044be20
    L_00430f01:
        test byte ptr [data_00474ca0],10h
    L_00430f08:
        jne short L_00430f71
    L_00430f0a:
        mov ecx,3
    L_00430f0f:
        mov eax,ebp
    L_00430f11:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00430f16:
        cmp dword ptr [data_00474c74],4
    L_00430f1d:
        mov ecx,7
    L_00430f22:
        jge short L_00430f3f
    L_00430f24:
        mov eax,1
    L_00430f29:
        mov dword ptr [data_00477848],4747B8h
    L_00430f33:
        mov dword ptr [data_00474c7c],eax
    L_00430f38:
        mov dword ptr [data_00474c80],eax
    L_00430f3d:
        jmp short L_00430f55
    L_00430f3f:
        mov dword ptr [data_00477848],4748D8h
    L_00430f49:
        mov dword ptr [data_00474c7c],ecx
    L_00430f4f:
        mov dword ptr [data_00474c80],ecx
    L_00430f55:
        push 40C00000h
    L_00430f5a:
        mov dword ptr [data_00491fb8],ecx
    L_00430f60:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_00430f65:
        pop edi
    L_00430f66:
        pop esi
    L_00430f67:
        pop ebx
    L_00430f68:
        mov eax,1
    L_00430f6d:
        pop ebp
    L_00430f6e:
        ret 4
    L_00430f71:
        mov esi,64h
    L_00430f76:
        mov edi,ebp
    L_00430f78:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430f7d:
        mov ecx,9
    L_00430f82:
        mov eax,ebp
    L_00430f84:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00430f89:
        pop edi
    L_00430f8a:
        pop esi
    L_00430f8b:
        pop ebx
    L_00430f8c:
        mov eax,1
    L_00430f91:
        pop ebp
    L_00430f92:
        ret 4
    L_00430f95:
        cmp dword ptr [ebp+2B4h],6
    L_00430f9c:
        jl short L_00430fcf
    L_00430f9e:
        mov esi,dword ptr [data_00474c68]
    L_00430fa4:
        add esi,96h
    L_00430faa:
        mov edi,ebp
    L_00430fac:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430fb1:
        mov esi,64h
    L_00430fb6:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00430fbb:
        mov ecx,7
    L_00430fc0:
        mov eax,ebp
    L_00430fc2:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_00430fc7:
        lea eax,[ebp+24h]
    L_00430fca:
        call asm_Score_InputHistoryStep_0044be70
    L_00430fcf:
        pop edi
    L_00430fd0:
        pop esi
    L_00430fd1:
        pop ebx
    L_00430fd2:
        mov eax,1
    L_00430fd7:
        pop ebp
    L_00430fd8:
        ret 4
        _emit 0x90
        _emit 0x7b
        _emit 0x0a
        _emit 0x43
        _emit 0x00
        _emit 0x3e
        _emit 0x0d
        _emit 0x43
        _emit 0x00
        _emit 0x63
        _emit 0x0d
        _emit 0x43
        _emit 0x00
        _emit 0x7d
        _emit 0x0e
        _emit 0x43
        _emit 0x00
        _emit 0x95
        _emit 0x0f
        _emit 0x43
        _emit 0x00
    }
}
