#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042CDF0..0x0042D212: FUN_0042cdf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042cdf0_0042cdf0() {
    __asm {
    L_0042cdf0:
        push ebx
    L_0042cdf1:
        mov ebx,eax
    L_0042cdf3:
        mov eax,dword ptr [ebx+1Ch]
    L_0042cdf6:
        cmp eax,1
    L_0042cdf9:
        push esi
    L_0042cdfa:
        push edi
    L_0042cdfb:
        je short L_0042ce02
    L_0042cdfd:
        cmp eax,2
    L_0042ce00:
        jne short L_0042ce25
    L_0042ce02:
        mov ecx,dword ptr [data_00474ca4]
    L_0042ce08:
        mov eax,dword ptr [data_00474e30]
    L_0042ce0d:
        inc ecx
    L_0042ce0e:
        test eax,160Bh
    L_0042ce13:
        mov dword ptr [data_00474ca4],ecx
    L_0042ce19:
        je short L_0042ce3e
    L_0042ce1b:
        mov dword ptr [data_00474ca4],0
    L_0042ce25:
        mov edi,dword ptr [data_00491c00]
    L_0042ce2b:
        mov eax,dword ptr [ebx+1Ch]
    L_0042ce2e:
        cmp eax,10h
    L_0042ce31:
        ja asm_target_0042d19f
    L_0042ce37:
        jmp dword ptr [eax*4+42D214h]
    L_0042ce3e:
        cmp dword ptr [data_00474ca4],384h
    L_0042ce48:
        jl short L_0042ce25
    L_0042ce4a:
        mov eax,dword ptr [data_00474ca0]
    L_0042ce4f:
        mov ecx,dword ptr [data_00474ca8]
    L_0042ce55:
        and eax,0FFFFFFBFh
    L_0042ce58:
        or eax,20h
    L_0042ce5b:
        mov dword ptr [data_00474ca0],eax
    L_0042ce60:
        mov eax,dword ptr [ecx*4+476FF8h]
    L_0042ce67:
        mov edx,477710h
    L_0042ce6c:
        sub edx,eax
    L_0042ce6e:
        mov edi,edi
    L_0042ce70:
        mov cl,byte ptr [eax]
    L_0042ce72:
        mov byte ptr [edx+eax],cl
    L_0042ce75:
        inc eax
    L_0042ce76:
        test cl,cl
    L_0042ce78:
        jne short L_0042ce70
    L_0042ce7a:
        push 477710h
    L_0042ce7f:
        call asm_StageManager_CreateRetail_004296f0
    L_0042ce84:
        mov edx,dword ptr [data_00474ca8]
    L_0042ce8a:
        inc edx
    L_0042ce8b:
        and edx,80000003h
    L_0042ce91:
        mov esi,eax
    L_0042ce93:
        jns short L_0042ce9a
    L_0042ce95:
        dec edx
    L_0042ce96:
        or edx,0FFFFFFFCh
    L_0042ce99:
        inc edx
    L_0042ce9a:
        mov dword ptr [data_00474ca8],edx
    L_0042cea0:
        xor eax,eax
    L_0042cea2:
        lea ecx,[esi+0B0h]
    L_0042cea8:
        cmp dword ptr [ecx],0
    L_0042ceab:
        jne short L_0042ceb6
    L_0042cead:
        inc eax
    L_0042ceae:
        add ecx,24h
    L_0042ceb1:
        cmp eax,8
    L_0042ceb4:
        jl short L_0042cea8
    L_0042ceb6:
        lea ecx,[eax+eax*2]
    L_0042ceb9:
        mov dword ptr [data_00474c7c],eax
    L_0042cebe:
        mov dword ptr [data_00474c80],eax
    L_0042cec3:
        mov dword ptr [data_00491fb8],0Ch
    L_0042cecd:
        mov eax,dword ptr [esi+18h]
    L_0042ced0:
        mov edx,dword ptr [eax+50h]
    L_0042ced3:
        shl ecx,4
    L_0042ced6:
        add ecx,474788h
    L_0042cedc:
        mov dword ptr [data_00474c68],edx
    L_0042cee2:
        mov edx,dword ptr [data_00474c74]
    L_0042cee8:
        mov dword ptr [data_00477848],ecx
    L_0042ceee:
        mov ecx,dword ptr [eax+54h]
    L_0042cef1:
        mov dword ptr [data_00474c6c],ecx
    L_0042cef7:
        mov dword ptr [data_00474c78],edx
    L_0042cefd:
        mov eax,dword ptr [eax+58h]
    L_0042cf00:
        push esi
    L_0042cf01:
        mov dword ptr [data_00474c74],eax
    L_0042cf06:
        call asm_FUN_004294a0_004294a0
    L_0042cf0b:
        push esi
    L_0042cf0c:
        call asm_free_004524a1
    L_0042cf11:
        mov eax,dword ptr [ebx+1Ch]
    L_0042cf14:
        xor ecx,ecx
    L_0042cf16:
        add esp,4
    L_0042cf19:
        cmp eax,1
    L_0042cf1c:
        setne cl
    L_0042cf1f:
        mov dword ptr [data_00474ca4],0
    L_0042cf29:
        mov edi,ecx
    L_0042cf2b:
        mov dword ptr [data_00491c00],edi
    L_0042cf31:
        jmp asm_target_0042ce2b
    L_0042cf36:
        mov esi,dword ptr [data_00491c10]
    L_0042cf3c:
        mov edx,dword ptr [esi+3AD084h]
    L_0042cf42:
        mov eax,esi
    L_0042cf44:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0042cf49:
        mov edx,dword ptr [esi+3AD088h]
    L_0042cf4f:
        mov eax,esi
    L_0042cf51:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0042cf56:
        mov edx,dword ptr [esi+3AD074h]
    L_0042cf5c:
        mov eax,esi
    L_0042cf5e:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0042cf63:
        mov edx,dword ptr [esi+3AD078h]
    L_0042cf69:
        mov eax,esi
    L_0042cf6b:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0042cf70:
        mov edx,dword ptr [esi+3AD06Ch]
    L_0042cf76:
        mov eax,esi
    L_0042cf78:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0042cf7d:
        mov esi,dword ptr [g_ascii_manager]
    L_0042cf83:
        add esi,89A4h
    L_0042cf89:
        mov eax,esi
    L_0042cf8b:
        call asm_FUN_00409e50_00409e50
    L_0042cf90:
        cmp edi,3
    L_0042cf93:
        mov dword ptr [esi],0
    L_0042cf99:
        jne short L_0042d00a
    L_0042cf9b:
        lea eax,[ebx+24h]
    L_0042cf9e:
        mov dword ptr [ebx+2Ch],0Ah
    L_0042cfa5:
        mov ecx,dword ptr [eax+8]
    L_0042cfa8:
        test ecx,ecx
    L_0042cfaa:
        je short L_0042cfb9
    L_0042cfac:
        jg short L_0042cfb3
    L_0042cfae:
        dec ecx
    L_0042cfaf:
        mov dword ptr [eax],ecx
    L_0042cfb1:
        jmp short L_0042cfbf
    L_0042cfb3:
        xor ecx,ecx
    L_0042cfb5:
        mov dword ptr [eax],ecx
    L_0042cfb7:
        jmp short L_0042cfbf
    L_0042cfb9:
        mov dword ptr [eax],0
    L_0042cfbf:
        call asm_Score_InputHistorySave_0044be20
    L_0042cfc4:
        mov ecx,0Fh
    L_0042cfc9:
        mov eax,ebx
    L_0042cfcb:
        call asm_Title_DisableTimerWithOwner
    L_0042cfd0:
        push ebx
    L_0042cfd1:
        mov edi,5Bh
    L_0042cfd6:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042cfdb:
        mov esi,9
    L_0042cfe0:
        mov ecx,edi
    L_0042cfe2:
        mov eax,ebx
    L_0042cfe4:
        call asm_FUN_0042c770_0042c770
    L_0042cfe9:
        mov eax,dword ptr [ebx+10h]
    L_0042cfec:
        mov ecx,dword ptr [eax+4]
    L_0042cfef:
        or ecx,2
    L_0042cff2:
        mov dword ptr [data_00491c00],1
    L_0042cffc:
        mov dword ptr [eax+4],ecx
    L_0042cfff:
        push ebx
    L_0042d000:
        call asm_FUN_00432cb0_00432cb0
    L_0042d005:
        jmp asm_target_0042d19f
    L_0042d00a:
        test byte ptr [data_00474ca0],20h
    L_0042d011:
        jne short L_0042d030
    L_0042d013:
        push 46F018h
    L_0042d018:
        push 0
    L_0042d01a:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_0042d01f:
        push 0
    L_0042d021:
        push 0
    L_0042d023:
        call asm_Sound_PlayDummyRetail_00420b10
    L_0042d028:
        mov edi,dword ptr [data_00491c00]
    L_0042d02e:
        jmp short L_0042d03c
    L_0042d030:
        mov edx,dword ptr [data_00474c78]
    L_0042d036:
        mov dword ptr [data_00474c74],edx
    L_0042d03c:
        mov ecx,dword ptr [data_00474ca0]
    L_0042d042:
        and ecx,0FFFFFFDFh
    L_0042d045:
        test edi,edi
    L_0042d047:
        mov dword ptr [data_00474ca0],ecx
    L_0042d04d:
        jne short L_0042d06f
    L_0042d04f:
        mov ecx,1
    L_0042d054:
        mov eax,ebx
    L_0042d056:
        call asm_Title_DisableTimerWithOwner
    L_0042d05b:
        mov dword ptr [data_00491c00],1
    L_0042d065:
        call asm_FUN_0042d300_0042d300
    L_0042d06a:
        jmp asm_target_0042d19f
    L_0042d06f:
        cmp edi,1
    L_0042d072:
        jne short L_0042d0c7
    L_0042d074:
        cmp dword ptr [data_00474c74],4
    L_0042d07b:
        jne short L_0042d09f
    L_0042d07d:
        mov eax,dword ptr [ebx+2Ch]
    L_0042d080:
        test eax,eax
    L_0042d082:
        je short L_0042d098
    L_0042d084:
        cmp eax,edi
    L_0042d086:
        jg short L_0042d08e
    L_0042d088:
        dec eax
    L_0042d089:
        mov dword ptr [ebx+24h],eax
    L_0042d08c:
        jmp short L_0042d09f
    L_0042d08e:
        mov eax,1
    L_0042d093:
        mov dword ptr [ebx+24h],eax
    L_0042d096:
        jmp short L_0042d09f
    L_0042d098:
        mov dword ptr [ebx+24h],1
    L_0042d09f:
        mov ecx,2
    L_0042d0a4:
        mov eax,ebx
    L_0042d0a6:
        call asm_Title_DisableTimerWithOwner
    L_0042d0ab:
        push ebx
    L_0042d0ac:
        mov edi,5Bh
    L_0042d0b1:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d0b6:
        mov eax,dword ptr [ebx+10h]
    L_0042d0b9:
        or dword ptr [eax+4],2
    L_0042d0bd:
        call asm_FUN_0042d420_0042d420
    L_0042d0c2:
        jmp asm_target_0042d19f
    L_0042d0c7:
        cmp edi,2
    L_0042d0ca:
        jne short L_0042d065
    L_0042d0cc:
        lea eax,[ebx+24h]
    L_0042d0cf:
        mov dword ptr [ebx+2Ch],0Ah
    L_0042d0d6:
        mov ecx,dword ptr [eax+8]
    L_0042d0d9:
        test ecx,ecx
    L_0042d0db:
        je short L_0042d0f0
    L_0042d0dd:
        cmp ecx,3
    L_0042d0e0:
        jg short L_0042d0e7
    L_0042d0e2:
        dec ecx
    L_0042d0e3:
        mov dword ptr [eax],ecx
    L_0042d0e5:
        jmp short L_0042d0f6
    L_0042d0e7:
        mov ecx,3
    L_0042d0ec:
        mov dword ptr [eax],ecx
    L_0042d0ee:
        jmp short L_0042d0f6
    L_0042d0f0:
        mov dword ptr [eax],3
    L_0042d0f6:
        call asm_Score_InputHistorySave_0044be20
    L_0042d0fb:
        mov ecx,0Ch
    L_0042d100:
        mov eax,ebx
    L_0042d102:
        call asm_Title_DisableTimerWithOwner
    L_0042d107:
        push ebx
    L_0042d108:
        mov edi,5Bh
    L_0042d10d:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_0042d112:
        mov esi,9
    L_0042d117:
        mov ecx,edi
    L_0042d119:
        mov eax,ebx
    L_0042d11b:
        call asm_FUN_0042c770_0042c770
    L_0042d120:
        mov eax,dword ptr [ebx+10h]
    L_0042d123:
        mov ecx,dword ptr [eax+4]
    L_0042d126:
        or ecx,2
    L_0042d129:
        mov dword ptr [data_00491c00],1
    L_0042d133:
        mov dword ptr [eax+4],ecx
    L_0042d136:
        push ebx
    L_0042d137:
        call asm_FUN_004315c0_004315c0
    L_0042d13c:
        jmp short L_0042d19f
    L_0042d13e:
        push ebx
    L_0042d13f:
        call asm_FUN_0042d920_0042d920
    L_0042d144:
        jmp short L_0042d19f
    L_0042d146:
        call asm_FUN_0042f540_0042f540
    L_0042d14b:
        jmp short L_0042d19f
    L_0042d14d:
        mov eax,dword ptr [data_00491ff4]
    L_0042d152:
        shr eax,0Ch
    L_0042d155:
        not eax
    L_0042d157:
        and eax,1
    L_0042d15a:
        or eax,2
    L_0042d15d:
        mov dword ptr [data_00491fb8],eax
    L_0042d162:
        call asm_GameState_DispatchDummy_00420c00
    L_0042d167:
        jmp short L_0042d19f
    L_0042d169:
        push ebx
    L_0042d16a:
        call asm_FUN_00430320_00430320
    L_0042d16f:
        jmp short L_0042d19f
    L_0042d171:
        push ebx
    L_0042d172:
        call asm_FUN_004306a0_004306a0
    L_0042d177:
        jmp short L_0042d19f
    L_0042d179:
        push ebx
    L_0042d17a:
        call asm_FUN_00430a60_00430a60
    L_0042d17f:
        jmp short L_0042d19f
    L_0042d181:
        push ebx
    L_0042d182:
        call asm_FUN_00430ff0_00430ff0
    L_0042d187:
        jmp short L_0042d19f
    L_0042d189:
        push ebx
    L_0042d18a:
        call asm_FUN_00433ef0_00433ef0
    L_0042d18f:
        jmp short L_0042d19f
    L_0042d191:
        push ebx
    L_0042d192:
        call asm_FUN_00431ee0_00431ee0
    L_0042d197:
        jmp short L_0042d19f
    L_0042d199:
        push ebx
    L_0042d19a:
        call asm_FUN_00433570_00433570
    L_0042d19f:
        mov edx,dword ptr [ebx+2B4h]
    L_0042d1a5:
        mov ecx,dword ptr [ebx+2BCh]
    L_0042d1ab:
        mov dword ptr [ebx+2B0h],edx
    L_0042d1b1:
        fld dword ptr [ecx]
    L_0042d1b3:
        fcomp dword ptr [data_00470b68]
    L_0042d1b9:
        fnstsw ax
    L_0042d1bb:
        test ah,41h
    L_0042d1be:
        jne short L_0042d1f1
    L_0042d1c0:
        fld dword ptr [ecx]
    L_0042d1c2:
        fcomp dword ptr [data_00470b64]
    L_0042d1c8:
        fnstsw ax
    L_0042d1ca:
        test ah,5
    L_0042d1cd:
        jp short L_0042d1f1
    L_0042d1cf:
        fld dword ptr [ebx+2B8h]
    L_0042d1d5:
        pop edi
    L_0042d1d6:
        fadd dword ptr [data_00470afc]
    L_0042d1dc:
        inc edx
    L_0042d1dd:
        pop esi
    L_0042d1de:
        mov dword ptr [ebx+2B4h],edx
    L_0042d1e4:
        fstp dword ptr [ebx+2B8h]
    L_0042d1ea:
        mov eax,1
    L_0042d1ef:
        pop ebx
    L_0042d1f0:
        ret
    L_0042d1f1:
        fld dword ptr [ecx]
    L_0042d1f3:
        fadd dword ptr [ebx+2B8h]
    L_0042d1f9:
        fst dword ptr [ebx+2B8h]
    L_0042d1ff:
        call asm_FUN_00463b2c_00463b2c
    L_0042d204:
        pop edi
    L_0042d205:
        mov dword ptr [ebx+2B4h],eax
    L_0042d20b:
        pop esi
    L_0042d20c:
        mov eax,1
    L_0042d211:
        pop ebx
    L_0042d212:
        ret
        _emit 0x90
        _emit 0x36
        _emit 0xcf
        _emit 0x42
        _emit 0x00
        _emit 0x65
        _emit 0xd0
        _emit 0x42
        _emit 0x00
        _emit 0xb6
        _emit 0xd0
        _emit 0x42
        _emit 0x00
        _emit 0x4d
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x3e
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x46
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x69
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x71
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x79
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x81
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x62
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x91
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x36
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x62
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0x89
        _emit 0xd1
        _emit 0x42
        _emit 0x00
        _emit 0xff
        _emit 0xcf
        _emit 0x42
        _emit 0x00
        _emit 0x99
        _emit 0xd1
        _emit 0x42
        _emit 0x00
    }
}
