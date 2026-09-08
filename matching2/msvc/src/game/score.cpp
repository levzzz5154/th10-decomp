#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x00408030..0x004080F6: ScoreState_ActivateFromResultRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreState_ActivateFromResultRetail_00408030() {
    __asm {
    L_00408030:
        push ecx
    L_00408031:
        mov ax,word ptr [esi+446h]
    L_00408038:
        cmp ax,2
    L_0040803c:
        je short L_00408048
    L_0040803e:
        cmp ax,1
    L_00408042:
        je short L_00408048
    L_00408044:
        xor eax,eax
    L_00408046:
        pop ecx
    L_00408047:
        ret
    L_00408048:
        push 41000000h
    L_0040804d:
        lea ecx,[esi+3B4h]
    L_00408053:
        push 41000000h
    L_00408058:
        call asm_OutsideAxisAlignedBounds_004086b0
    L_0040805d:
        test eax,eax
    L_0040805f:
        mov word ptr [esi+30Ch],1
    L_00408068:
        mov word ptr [esi+446h],3
    L_00408071:
        jne short L_004080ed
    L_00408073:
        mov eax,dword ptr [esi+438h]
    L_00408079:
        push ebp
    L_0040807a:
        xor ebp,ebp
    L_0040807c:
        cmp eax,ebp
    L_0040807e:
        jl short L_0040809c
    L_00408080:
        mov edx,dword ptr [data_004776f0]
    L_00408086:
        push edi
    L_00408087:
        push eax
    L_00408088:
        lea eax,[esp+0Ch]
    L_0040808c:
        push eax
    L_0040808d:
        mov eax,dword ptr [edx+3E0B50h]
    L_00408093:
        push eax
    L_00408094:
        mov edi,ecx
    L_00408096:
        call asm_PlayerAnimation_Create_00448db0
    L_0040809b:
        pop edi
    L_0040809c:
        mov eax,dword ptr [esi+408h]
    L_004080a2:
        test al,1
    L_004080a4:
        jne short L_004080cf
    L_004080a6:
        or eax,1
    L_004080a9:
        mov dword ptr [esi+3FCh],ebp
    L_004080af:
        mov dword ptr [esi+3F8h],0FFF0BDC1h
    L_004080b9:
        mov dword ptr [esi+400h],ebp
    L_004080bf:
        mov dword ptr [esi+404h],476F78h
    L_004080c9:
        mov dword ptr [esi+408h],eax
    L_004080cf:
        mov dword ptr [esi+3FCh],ebp
    L_004080d5:
        mov dword ptr [esi+400h],ebp
    L_004080db:
        mov dword ptr [esi+3F8h],0FFFFFFFFh
    L_004080e5:
        pop ebp
    L_004080e6:
        mov eax,1
    L_004080eb:
        pop ecx
    L_004080ec:
        ret
    L_004080ed:
        or dword ptr [esi],8
    L_004080f0:
        mov eax,1
    L_004080f5:
        pop ecx
    L_004080f6:
        ret
    }
}

// 0x00408660..0x004086AF: ?WrappedAngleDifference@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_WrappedAngleDifference_00408660() {
    __asm {
    L_00408660:
        fld dword ptr [esp+4]
    L_00408664:
        fsub dword ptr [esp+8]
    L_00408668:
        fcom dword ptr [data_00470b18]
    L_0040866e:
        fnstsw ax
    L_00408670:
        test ah,41h
    L_00408673:
        jne short L_00408688
    L_00408675:
        fstp st(0)
    L_00408677:
        fld dword ptr [esp+8]
    L_0040867b:
        fadd dword ptr [data_00470b14]
    L_00408681:
        fsubr dword ptr [esp+4]
    L_00408685:
        ret 8
    L_00408688:
        fld dword ptr [esp+8]
    L_0040868c:
        fsub dword ptr [esp+4]
    L_00408690:
        fcomp dword ptr [data_00470b18]
    L_00408696:
        fnstsw ax
    L_00408698:
        test ah,41h
    L_0040869b:
        jne short L_004086ad
    L_0040869d:
        fstp st(0)
    L_0040869f:
        fld dword ptr [esp+8]
    L_004086a3:
        fsub dword ptr [data_00470b14]
    L_004086a9:
        fsubr dword ptr [esp+4]
    L_004086ad:
        ret 8
    }
}

// 0x00408750..0x0040876D: Score_SetPolarVector
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_SetPolarVector_00408750() {
    __asm {
    L_00408750:
        push ecx
    L_00408751:
        mov dword ptr [esp],ecx
    L_00408754:
        mov eax,dword ptr [esp]
    L_00408757:
        fld dword ptr [esp+8]
    L_0040875b:
        fsincos
    L_0040875d:
        fmul dword ptr [esp+0Ch]
    L_00408761:
        fstp dword ptr [eax]
    L_00408763:
        fmul dword ptr [esp+0Ch]
    L_00408767:
        fstp dword ptr [eax+4]
    L_0040876a:
        pop ecx
    L_0040876b:
        ret 8
    }
}

// 0x004088C0..0x0040890A: ?CountPatternMatches@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CountPatternMatches_004088c0() {
    __asm {
    L_004088c0:
        xor eax,eax
    L_004088c2:
        xor ecx,ecx
    L_004088c4:
        push esi
    L_004088c5:
        movsx esi,byte ptr [ecx+4743C0h]
    L_004088cc:
        cmp esi,edx
    L_004088ce:
        jne short L_004088d1
    L_004088d0:
        inc eax
    L_004088d1:
        movsx esi,byte ptr [ecx+4743C1h]
    L_004088d8:
        cmp esi,edx
    L_004088da:
        jne short L_004088dd
    L_004088dc:
        inc eax
    L_004088dd:
        movsx esi,byte ptr [ecx+4743C2h]
    L_004088e4:
        cmp esi,edx
    L_004088e6:
        jne short L_004088e9
    L_004088e8:
        inc eax
    L_004088e9:
        movsx esi,byte ptr [ecx+4743C3h]
    L_004088f0:
        cmp esi,edx
    L_004088f2:
        jne short L_004088f5
    L_004088f4:
        inc eax
    L_004088f5:
        movsx esi,byte ptr [ecx+4743C4h]
    L_004088fc:
        cmp esi,edx
    L_004088fe:
        jne short L_00408901
    L_00408900:
        inc eax
    L_00408901:
        add ecx,5
    L_00408904:
        cmp ecx,6Eh
    L_00408907:
        jl short L_004088c5
    L_00408909:
        pop esi
    L_0040890a:
        ret
    }
}

// 0x004089C0..0x00408A92: FUN_004089c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004089c0_004089c0() {
    __asm {
    L_004089c0:
        push esi
    L_004089c1:
        push edi
    L_004089c2:
        push 409220h
    L_004089c7:
        call asm_SchedulerCallback_Create_00449ed0
    L_004089cc:
        mov esi,eax
    L_004089ce:
        mov edx,dword ptr [esi+4]
    L_004089d1:
        mov eax,dword ptr [data_00491be4]
    L_004089d6:
        and edx,0FFFFFFFDh
    L_004089d9:
        push eax
    L_004089da:
        mov edi,16h
    L_004089df:
        mov dword ptr [esi+20h],ebx
    L_004089e2:
        mov dword ptr [esi+4],edx
    L_004089e5:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004089ea:
        push 409230h
    L_004089ef:
        mov dword ptr [ebx+8],esi
    L_004089f2:
        call asm_SchedulerCallback_Create_00449ed0
    L_004089f7:
        mov ecx,dword ptr [data_00491be4]
    L_004089fd:
        mov esi,eax
    L_004089ff:
        and dword ptr [esi+4],0FFFFFFFDh
    L_00408a03:
        push ecx
    L_00408a04:
        mov edi,0Eh
    L_00408a09:
        mov dword ptr [esi+20h],ebx
    L_00408a0c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00408a11:
        push 409270h
    L_00408a16:
        mov dword ptr [ebx+0Ch],esi
    L_00408a19:
        call asm_SchedulerCallback_Create_00449ed0
    L_00408a1e:
        mov edx,dword ptr [data_00491be4]
    L_00408a24:
        mov esi,eax
    L_00408a26:
        mov eax,dword ptr [esi+4]
    L_00408a29:
        and eax,0FFFFFFFDh
    L_00408a2c:
        push edx
    L_00408a2d:
        mov edi,25h
    L_00408a32:
        mov dword ptr [esi+20h],ebx
    L_00408a35:
        mov dword ptr [esi+4],eax
    L_00408a38:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00408a3d:
        mov dword ptr [ebx+37ACh],esi
    L_00408a43:
        mov eax,dword ptr [ebx+3744h]
    L_00408a49:
        xor ecx,ecx
    L_00408a4b:
        test al,1
    L_00408a4d:
        pop edi
    L_00408a4e:
        pop esi
    L_00408a4f:
        jne short L_00408a7a
    L_00408a51:
        or eax,1
    L_00408a54:
        mov dword ptr [ebx+3738h],ecx
    L_00408a5a:
        mov dword ptr [ebx+3734h],0FFF0BDC1h
    L_00408a64:
        mov dword ptr [ebx+373Ch],ecx
    L_00408a6a:
        mov dword ptr [ebx+3740h],476F78h
    L_00408a74:
        mov dword ptr [ebx+3744h],eax
    L_00408a7a:
        mov dword ptr [ebx+3738h],ecx
    L_00408a80:
        mov dword ptr [ebx+373Ch],ecx
    L_00408a86:
        mov dword ptr [ebx+3734h],0FFFFFFFFh
    L_00408a90:
        xor eax,eax
    L_00408a92:
        ret
    }
}

// 0x00408D60..0x00408ED9: FUN_00408d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408d60_00408d60() {
    __asm {
    L_00408d60:
        mov al,byte ptr [edi+378Ch]
    L_00408d66:
        sub esp,1Ch
    L_00408d69:
        test al,1
    L_00408d6b:
        je asm_target_00409178
    L_00408d71:
        cmp dword ptr [edi+3738h],3Ch
    L_00408d78:
        jl short L_00408d86
    L_00408d7a:
        mov eax,dword ptr [data_004776e8]
    L_00408d7f:
        and dword ptr [eax+2A18h],0FFFFFFFEh
    L_00408d86:
        cmp dword ptr [edi+3738h],12Ch
    L_00408d90:
        push ebx
    L_00408d91:
        push ebp
    L_00408d92:
        push esi
    L_00408d93:
        jl short L_00408de2
    L_00408d95:
        test byte ptr [edi+378Ch],8
    L_00408d9c:
        jne short L_00408de2
    L_00408d9e:
        mov ecx,dword ptr [edi+3794h]
    L_00408da4:
        mov eax,66666667h
    L_00408da9:
        imul ecx
    L_00408dab:
        sar edx,2
    L_00408dae:
        mov eax,edx
    L_00408db0:
        shr eax,1Fh
    L_00408db3:
        add edx,eax
    L_00408db5:
        mov eax,ecx
    L_00408db7:
        mov ecx,dword ptr [edi+3798h]
    L_00408dbd:
        sub eax,edx
    L_00408dbf:
        cdq
    L_00408dc0:
        sub ecx,12Ch
    L_00408dc6:
        idiv ecx
    L_00408dc8:
        mov ecx,dword ptr [edi+3790h]
    L_00408dce:
        mov esi,0Ah
    L_00408dd3:
        sub ecx,eax
    L_00408dd5:
        mov eax,ecx
    L_00408dd7:
        cdq
    L_00408dd8:
        idiv esi
    L_00408dda:
        sub ecx,edx
    L_00408ddc:
        mov dword ptr [edi+3790h],ecx
    L_00408de2:
        lea edx,[edi+10h]
    L_00408de5:
        push edx
    L_00408de6:
        call asm_FUN_0043ee30_0043ee30
    L_00408deb:
        lea eax,[edi+3BCh]
    L_00408df1:
        push eax
    L_00408df2:
        call asm_FUN_0043ee30_0043ee30
    L_00408df7:
        mov edx,dword ptr [edi+3738h]
    L_00408dfd:
        mov ecx,dword ptr [edi+3740h]
    L_00408e03:
        mov dword ptr [edi+3734h],edx
    L_00408e09:
        fld dword ptr [ecx]
    L_00408e0b:
        fcomp dword ptr [data_00470b68]
    L_00408e11:
        fnstsw ax
    L_00408e13:
        test ah,41h
    L_00408e16:
        jne short L_00408e42
    L_00408e18:
        fld dword ptr [ecx]
    L_00408e1a:
        fcomp dword ptr [data_00470b64]
    L_00408e20:
        fnstsw ax
    L_00408e22:
        test ah,5
    L_00408e25:
        jp short L_00408e42
    L_00408e27:
        fld dword ptr [edi+373Ch]
    L_00408e2d:
        inc edx
    L_00408e2e:
        fadd dword ptr [data_00470afc]
    L_00408e34:
        mov dword ptr [edi+3738h],edx
    L_00408e3a:
        fstp dword ptr [edi+373Ch]
    L_00408e40:
        jmp short L_00408e5b
    L_00408e42:
        fld dword ptr [ecx]
    L_00408e44:
        fadd dword ptr [edi+373Ch]
    L_00408e4a:
        fst dword ptr [edi+373Ch]
    L_00408e50:
        call asm_FUN_00463b2c_00463b2c
    L_00408e55:
        mov dword ptr [edi+3738h],eax
    L_00408e5b:
        cmp dword ptr [edi+3738h],78h
    L_00408e62:
        jl asm_target_00408f7c
    L_00408e68:
        test byte ptr [edi+378Ch],4
    L_00408e6f:
        jne asm_target_00408efb
    L_00408e75:
        mov ecx,dword ptr [data_00477834]
    L_00408e7b:
        fld dword ptr [ecx+3C4h]
    L_00408e81:
        fcomp dword ptr [data_00470c80]
    L_00408e87:
        fnstsw ax
    L_00408e89:
        test ah,5
    L_00408e8c:
        jp asm_target_00408f7c
    L_00408e92:
        lea ebp,[edi+768h]
    L_00408e98:
        mov ebx,3
    L_00408e9d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408ea0:
        mov esi,3
    L_00408ea5:
        mov eax,ebp
    L_00408ea7:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00408eac:
        add ebp,4
    L_00408eaf:
        dec ebx
    L_00408eb0:
        jne short L_00408ea0
    L_00408eb2:
        lea eax,[edi+0A7Ch]
    L_00408eb8:
        mov ecx,8
    L_00408ebd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408ec0:
        mov word ptr [eax],3
    L_00408ec5:
        add eax,3ACh
    L_00408eca:
        dec ecx
    L_00408ecb:
        jne short L_00408ec0
    L_00408ecd:
        lea eax,[edi+27DCh]
    L_00408ed3:
        mov ecx,5
    L_00408ed8:
        TH10_REL8(0xeb, 0x00408ed8, VA_asm_FUN_00408d60_part_00408ee0)
    }
}

// 0x00408EE0..0x00408F59: FUN_00408d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408d60_part_00408ee0() {
    __asm {
    L_00408ee0:
        mov word ptr [eax],3
    L_00408ee5:
        add eax,3ACh
    L_00408eea:
        dec ecx
    L_00408eeb:
        jne short L_00408ee0
    L_00408eed:
        mov eax,dword ptr [edi+378Ch]
    L_00408ef3:
        or eax,4
    L_00408ef6:
        jmp asm_target_00408f76
    L_00408efb:
        mov edx,dword ptr [data_00477834]
    L_00408f01:
        fld dword ptr [edx+3C4h]
    L_00408f07:
        fcomp dword ptr [data_00470bf4]
    L_00408f0d:
        fnstsw ax
    L_00408f0f:
        test ah,41h
    L_00408f12:
        TH10_REL8(0x75, 0x00408f12, VA_asm_target_00408f7c)
    L_00408f14:
        lea ebp,[edi+768h]
    L_00408f1a:
        mov ebx,3
    L_00408f1f:
        nop
    L_00408f20:
        mov esi,2
    L_00408f25:
        mov eax,ebp
    L_00408f27:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00408f2c:
        add ebp,4
    L_00408f2f:
        dec ebx
    L_00408f30:
        jne short L_00408f20
    L_00408f32:
        lea eax,[edi+0A7Ch]
    L_00408f38:
        mov ecx,8
    L_00408f3d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408f40:
        mov word ptr [eax],2
    L_00408f45:
        add eax,3ACh
    L_00408f4a:
        dec ecx
    L_00408f4b:
        jne short L_00408f40
    L_00408f4d:
        lea eax,[edi+27DCh]
    L_00408f53:
        mov ecx,5
    L_00408f58:
        TH10_REL8(0xeb, 0x00408f58, VA_asm_FUN_00408d60_part_00408f60)
    }
}

// 0x00408F60..0x00409180: FUN_00408d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408d60_part_00408f60() {
    __asm {
    L_00408f60:
        mov word ptr [eax],2
    L_00408f65:
        add eax,3ACh
    L_00408f6a:
        dec ecx
    L_00408f6b:
        jne short L_00408f60
    L_00408f6d:
        mov eax,dword ptr [edi+378Ch]
    L_00408f73:
        and eax,0FFFFFFFBh
    L_00408f76:
        mov dword ptr [edi+378Ch],eax
    L_00408f7c:
        test byte ptr [edi+378Ch],2
    L_00408f83:
        je short L_00408feb
    L_00408f85:
        mov ecx,dword ptr [edi+3790h]
    L_00408f8b:
        mov esi,989680h
    L_00408f90:
        lea ebx,[edi+778h]
    L_00408f96:
        mov dword ptr [esp+0Ch],8
    L_00408f9e:
        mov edi,edi
    L_00408fa0:
        mov eax,ecx
    L_00408fa2:
        cdq
    L_00408fa3:
        idiv esi
    L_00408fa5:
        mov ecx,dword ptr [data_0047770c]
    L_00408fab:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00408fb1:
        mov ebp,edx
    L_00408fb3:
        lea edx,[eax+1Eh]
    L_00408fb6:
        mov eax,ebx
    L_00408fb8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00408fbd:
        push ebx
    L_00408fbe:
        call asm_FUN_0043ee30_0043ee30
    L_00408fc3:
        mov eax,66666667h
    L_00408fc8:
        imul esi
    L_00408fca:
        sar edx,2
    L_00408fcd:
        mov eax,edx
    L_00408fcf:
        shr eax,1Fh
    L_00408fd2:
        add eax,edx
    L_00408fd4:
        mov esi,eax
    L_00408fd6:
        mov eax,dword ptr [esp+0Ch]
    L_00408fda:
        add ebx,3ACh
    L_00408fe0:
        dec eax
    L_00408fe1:
        mov ecx,ebp
    L_00408fe3:
        mov dword ptr [esp+0Ch],eax
    L_00408fe7:
        jne short L_00408fa0
    L_00408fe9:
        jmp short L_0040900f
    L_00408feb:
        mov ecx,dword ptr [data_0047770c]
    L_00408ff1:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00408ff7:
        lea esi,[edi+0ED0h]
    L_00408ffd:
        mov edx,29h
    L_00409002:
        mov eax,esi
    L_00409004:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409009:
        push esi
    L_0040900a:
        call asm_FUN_0043ee30_0043ee30
    L_0040900f:
        mov eax,dword ptr [data_00474c68]
    L_00409014:
        mov edx,dword ptr [data_00474c6c]
    L_0040901a:
        mov esi,dword ptr [data_0047783c]
    L_00409020:
        lea ecx,[edx+eax*2]
    L_00409023:
        add ecx,eax
    L_00409025:
        mov eax,dword ptr [edi+3788h]
    L_0040902b:
        imul ecx,437Ch
    L_00409031:
        lea edx,[eax+eax*8]
    L_00409034:
        shl edx,4
    L_00409037:
        add ecx,esi
    L_00409039:
        mov eax,dword ptr [edx+ecx+624h]
    L_00409040:
        cmp eax,64h
    L_00409043:
        jl short L_0040904a
    L_00409045:
        mov eax,63h
    L_0040904a:
        cdq
    L_0040904b:
        mov ecx,0Ah
    L_00409050:
        idiv ecx
    L_00409052:
        mov esi,dword ptr [data_0047770c]
    L_00409058:
        mov ecx,dword ptr [esi+9EC8h]
    L_0040905e:
        lea ebx,[edi+24D8h]
    L_00409064:
        mov ebp,edx
    L_00409066:
        lea edx,[eax+1Eh]
    L_00409069:
        mov eax,ebx
    L_0040906b:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409070:
        mov ecx,dword ptr [esi+9EC8h]
    L_00409076:
        lea edx,[ebp+1Eh]
    L_00409079:
        lea eax,[edi+2884h]
    L_0040907f:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409084:
        mov eax,dword ptr [data_00474c68]
    L_00409089:
        mov edx,dword ptr [data_00474c6c]
    L_0040908f:
        mov ebp,dword ptr [data_0047783c]
    L_00409095:
        lea ecx,[edx+eax*2]
    L_00409098:
        add ecx,eax
    L_0040909a:
        mov eax,dword ptr [edi+3788h]
    L_004090a0:
        imul ecx,437Ch
    L_004090a6:
        lea edx,[eax+eax*8]
    L_004090a9:
        shl edx,4
    L_004090ac:
        add ecx,ebp
    L_004090ae:
        mov eax,dword ptr [edx+ecx+628h]
    L_004090b5:
        cmp eax,64h
    L_004090b8:
        jl short L_004090bf
    L_004090ba:
        mov eax,63h
    L_004090bf:
        cdq
    L_004090c0:
        mov ecx,0Ah
    L_004090c5:
        idiv ecx
    L_004090c7:
        mov ecx,dword ptr [esi+9EC8h]
    L_004090cd:
        mov ebp,edx
    L_004090cf:
        lea edx,[eax+1Eh]
    L_004090d2:
        lea eax,[edi+2FDCh]
    L_004090d8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004090dd:
        mov ecx,dword ptr [esi+9EC8h]
    L_004090e3:
        lea edx,[ebp+1Eh]
    L_004090e6:
        lea eax,[edi+3388h]
    L_004090ec:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004090f1:
        mov esi,5
    L_004090f6:
        push ebx
    L_004090f7:
        call asm_FUN_0043ee30_0043ee30
    L_004090fc:
        add ebx,3ACh
    L_00409102:
        dec esi
    L_00409103:
        jne short L_004090f6
    L_00409105:
        mov edx,dword ptr [data_00477704]
    L_0040910b:
        mov eax,dword ptr [edx+10h]
    L_0040910e:
        fld dword ptr [eax+1068h]
    L_00409114:
        lea esi,[edi+379Ch]
    L_0040911a:
        fsub dword ptr [esi]
    L_0040911c:
        add eax,1068h
    L_00409121:
        fld dword ptr [eax+4]
    L_00409124:
        mov edx,dword ptr [data_00491c10]
    L_0040912a:
        fsub dword ptr [esi+4]
    L_0040912d:
        fld dword ptr [eax+8]
    L_00409130:
        fsub dword ptr [esi+8]
    L_00409133:
        fstp dword ptr [esp+18h]
    L_00409137:
        fxch
    L_00409139:
        fmul dword ptr [data_00470c84]
    L_0040913f:
        fstp dword ptr [esp+1Ch]
    L_00409143:
        fmul dword ptr [data_00470c84]
    L_00409149:
        fld dword ptr [esp+18h]
    L_0040914d:
        fmul dword ptr [data_00470c84]
    L_00409153:
        fld dword ptr [esp+1Ch]
    L_00409157:
        fadd dword ptr [esi]
    L_00409159:
        fstp dword ptr [esi]
    L_0040915b:
        fxch
    L_0040915d:
        fadd dword ptr [esi+4]
    L_00409160:
        fstp dword ptr [esi+4]
    L_00409163:
        fadd dword ptr [esi+8]
    L_00409166:
        fstp dword ptr [esi+8]
    L_00409169:
        mov eax,dword ptr [edi+774h]
    L_0040916f:
        push eax
    L_00409170:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_00409175:
        pop esi
    L_00409176:
        pop ebp
    L_00409177:
        pop ebx
    L_00409178:
        mov eax,1
    L_0040917d:
        add esp,1Ch
    L_00409180:
        ret
    }
}

// 0x004091C0..0x004091D7: ?ReleaseFlaggedEntityArrays@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0() {
    __asm {
    L_004091c0:
        test byte ptr [ebx+378Ch],1
    L_004091c7:
        TH10_REL8(0x74, 0x004091c7, VA_asm_target_00409219)
    L_004091c9:
        push esi
    L_004091ca:
        push edi
    L_004091cb:
        lea esi,[ebx+778h]
    L_004091d1:
        mov edi,8
    L_004091d6:
        TH10_REL8(0xeb, 0x004091d6, VA_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_part_004091e0)
    }
}

// 0x004091E0..0x0040921E: ?ReleaseFlaggedEntityArrays@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_part_004091e0() {
    __asm {
    L_004091e0:
        mov ecx,dword ptr [data_00491c10]
    L_004091e6:
        mov eax,esi
    L_004091e8:
        call asm_FUN_004451c0_004451c0
    L_004091ed:
        add esi,3ACh
    L_004091f3:
        dec edi
    L_004091f4:
        jne short L_004091e0
    L_004091f6:
        lea esi,[ebx+24D8h]
    L_004091fc:
        mov edi,5
    L_00409201:
        mov ecx,dword ptr [data_00491c10]
    L_00409207:
        mov eax,esi
    L_00409209:
        call asm_FUN_004451c0_004451c0
    L_0040920e:
        add esi,3ACh
    L_00409214:
        dec edi
    L_00409215:
        jne short L_00409201
    L_00409217:
        pop edi
    L_00409218:
        pop esi
    L_00409219:
        mov eax,1
    L_0040921e:
        ret
    }
}

// 0x00409230..0x00409261: ?ReleaseFlaggedEntities@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ReleaseFlaggedEntities_ScoreRuntimeState_00409230() {
    __asm {
    L_00409230:
        push esi
    L_00409231:
        mov esi,ecx
    L_00409233:
        test byte ptr [esi+378Ch],1
    L_0040923a:
        je short L_0040925b
    L_0040923c:
        mov ecx,dword ptr [data_00491c10]
    L_00409242:
        lea eax,[esi+10h]
    L_00409245:
        call asm_FUN_004451c0_004451c0
    L_0040924a:
        mov ecx,dword ptr [data_00491c10]
    L_00409250:
        lea eax,[esi+3BCh]
    L_00409256:
        call asm_FUN_004451c0_004451c0
    L_0040925b:
        mov eax,1
    L_00409260:
        pop esi
    L_00409261:
        ret
    }
}

// 0x00409270..0x00409279: ?RunArrayReleaseCallback@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RunArrayReleaseCallback_ScoreRuntimeState_00409270() {
    __asm {
    L_00409270:
        push ebx
    L_00409271:
        mov ebx,ecx
    L_00409273:
        call asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0
    L_00409278:
        pop ebx
    L_00409279:
        ret
    }
}

// 0x00409D90..0x00409DBD: ?AddScaled@GameScore@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AddScaled_GameScore_00409d90() {
    __asm {
    L_00409d90:
        mov eax,66666667h
    L_00409d95:
        imul dword ptr [esp+4]
    L_00409d99:
        sar edx,2
    L_00409d9c:
        mov eax,edx
    L_00409d9e:
        shr eax,1Fh
    L_00409da1:
        add eax,edx
    L_00409da3:
        mov edx,dword ptr [ecx+4]
    L_00409da6:
        add edx,eax
    L_00409da8:
        mov eax,edx
    L_00409daa:
        cmp eax,3B9ACA00h
    L_00409daf:
        mov dword ptr [ecx+4],edx
    L_00409db2:
        jl short L_00409dbb
    L_00409db4:
        mov dword ptr [ecx+4],3B9AC9FFh
    L_00409dbb:
        ret 4
    }
}

// 0x00409E20..0x00409E3B: ?Retire@ScoreRuntimeCallbacks@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Retire_ScoreRuntimeCallbacks_00409e20() {
    __asm {
    L_00409e20:
        mov ecx,dword ptr [eax+8]
    L_00409e23:
        test ecx,ecx
    L_00409e25:
        mov edx,2
    L_00409e2a:
        je short L_00409e2f
    L_00409e2c:
        or dword ptr [ecx+4],edx
    L_00409e2f:
        mov ecx,dword ptr [eax+0Ch]
    L_00409e32:
        test ecx,ecx
    L_00409e34:
        je short L_00409e3b
    L_00409e36:
        mov eax,ecx
    L_00409e38:
        or dword ptr [eax+4],edx
    L_00409e3b:
        ret
    }
}

// 0x0040AC20..0x0040AC8C: ?UpdateInputState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_UpdateInputState_0040ac20() {
    __asm {
    L_0040ac20:
        push ecx
    L_0040ac21:
        xor eax,eax
    L_0040ac23:
        mov ax,word ptr [ecx+2Ch]
    L_0040ac27:
        push ebx
    L_0040ac28:
        push esi
    L_0040ac29:
        mov word ptr [ecx+4],0
    L_0040ac2f:
        mov edx,10h
    L_0040ac34:
        mov ebx,1
    L_0040ac39:
        mov dword ptr [esp+8],eax
    L_0040ac3d:
        lea eax,[ecx+38h]
    L_0040ac40:
        test byte ptr [esp+8],bl
    L_0040ac44:
        je short L_0040ac5a
    L_0040ac46:
        inc word ptr [eax]
    L_0040ac49:
        cmp word ptr [eax],1Ah
    L_0040ac4d:
        jb short L_0040ac5f
    L_0040ac4f:
        or word ptr [ecx+30h],bx
    L_0040ac53:
        TH10_ADD_M16_IMM16(TH10_R32_EAX, 0xfff8)
    L_0040ac58:
        jmp short L_0040ac5f
    L_0040ac5a:
        mov word ptr [eax],0
    L_0040ac5f:
        shr word ptr [esp+8],1
    L_0040ac64:
        add eax,2
    L_0040ac67:
        dec edx
    L_0040ac68:
        jne short L_0040ac40
    L_0040ac6a:
        xor eax,eax
    L_0040ac6c:
        mov ax,word ptr [ecx+2Ch]
    L_0040ac70:
        xor edx,edx
    L_0040ac72:
        mov dx,word ptr [ecx+2Eh]
    L_0040ac76:
        xor dx,ax
    L_0040ac79:
        mov esi,edx
    L_0040ac7b:
        and esi,eax
    L_0040ac7d:
        not eax
    L_0040ac7f:
        mov word ptr [ecx+32h],si
    L_0040ac83:
        and eax,edx
    L_0040ac85:
        pop esi
    L_0040ac86:
        mov word ptr [ecx+34h],ax
    L_0040ac8a:
        pop ebx
    L_0040ac8b:
        pop ecx
    L_0040ac8c:
        ret
    }
}

// 0x0040AC90..0x0040ACB4: ?SetInputMode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SetInputMode_0040ac90() {
    __asm {
    L_0040ac90:
        mov ecx,dword ptr [eax+3CCh]
    L_0040ac96:
        test ch,10h
    L_0040ac99:
        jne short L_0040aca8
    L_0040ac9b:
        mov ecx,dword ptr [esp+4]
    L_0040ac9f:
        mov dword ptr [eax+390h],ecx
    L_0040aca5:
        ret 4
    L_0040aca8:
        mov dword ptr [eax+390h],2
    L_0040acb2:
        ret 4
    }
}

// 0x0040ACE0..0x0040AD00: ?InputMaskActive@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InputMaskActive_0040ace0() {
    __asm {
    L_0040ace0:
        xor edx,edx
    L_0040ace2:
        mov dx,word ptr [ecx+6]
    L_0040ace6:
        and edx,eax
    L_0040ace8:
        test dx,dx
    L_0040aceb:
        jne short L_0040acfb
    L_0040aced:
        movzx ecx,word ptr [ecx+4]
    L_0040acf1:
        and ecx,eax
    L_0040acf3:
        test cx,cx
    L_0040acf6:
        jne short L_0040acfb
    L_0040acf8:
        xor eax,eax
    L_0040acfa:
        ret
    L_0040acfb:
        mov eax,1
    L_0040ad00:
        ret
    }
}

// 0x0040AD20..0x0040AD40: clamp the requested signed value to the
// counter's current upper bound. Negative requests become UINT_MAX.
unsigned int __fastcall UpdateBoundedCounter(
        unsigned int requested, unsigned int* counter) {
    unsigned int value = counter[2];
    if (value) {
        if ((int)requested >= (int)value)
            --value;
        else
            value = (((int)requested < 0) - 1) & requested;
    } else {
        value = requested;
    }
    *counter = value;
    return value;
}

// 0x0040B9D0..0x0040B9E1: ?ScoreOwnedObject_Destroy@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreOwnedObject_Destroy_0040b9d0() {
    __asm {
    L_0040b9d0:
        test esi,esi
    L_0040b9d2:
        je short L_0040b9e1
    L_0040b9d4:
        push esi
    L_0040b9d5:
        call asm_FUN_0040b7b0_0040b7b0
    L_0040b9da:
        push esi
    L_0040b9db:
        call asm_free_004524a1
    L_0040b9e0:
        pop ecx
    L_0040b9e1:
        ret
    }
}

// 0x00412E70..0x00412E9D: ?ScoreGauge_AddWithMinimum@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreGauge_AddWithMinimum_00412e70() {
    __asm {
    L_00412e70:
        mov eax,99999999h
    L_00412e75:
        imul dword ptr [esp+4]
    L_00412e79:
        sar edx,2
    L_00412e7c:
        mov eax,edx
    L_00412e7e:
        shr eax,1Fh
    L_00412e81:
        add eax,edx
    L_00412e83:
        mov edx,dword ptr [ecx+0Ch]
    L_00412e86:
        add edx,eax
    L_00412e88:
        mov eax,edx
    L_00412e8a:
        cmp eax,1388h
    L_00412e8f:
        mov dword ptr [ecx+0Ch],edx
    L_00412e92:
        jge short L_00412e9b
    L_00412e94:
        mov dword ptr [ecx+0Ch],1388h
    L_00412e9b:
        ret 4
    }
}

// 0x0041BE80..0x0041BEAD: ?AddScaled@ScoreCounter@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AddScaled_ScoreCounter_0041be80() {
    __asm {
    L_0041be80:
        mov eax,66666667h
    L_0041be85:
        imul dword ptr [esp+4]
    L_0041be89:
        sar edx,2
    L_0041be8c:
        mov eax,edx
    L_0041be8e:
        shr eax,1Fh
    L_0041be91:
        add eax,edx
    L_0041be93:
        mov edx,dword ptr [ecx+0Ch]
    L_0041be96:
        add edx,eax
    L_0041be98:
        mov eax,edx
    L_0041be9a:
        cmp eax,1869Fh
    L_0041be9f:
        mov dword ptr [ecx+0Ch],edx
    L_0041bea2:
        jle short L_0041beab
    L_0041bea4:
        mov dword ptr [ecx+0Ch],1869Fh
    L_0041beab:
        ret 4
    }
}

// 0x0041BEB0..0x0041BECD: FUN_0041beb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041beb0_0041beb0() {
    __asm {
    L_0041beb0:
        push ecx
    L_0041beb1:
        mov dword ptr [esp],ecx
    L_0041beb4:
        mov eax,dword ptr [esp]
    L_0041beb7:
        fld dword ptr [esp+8]
    L_0041bebb:
        fsincos
    L_0041bebd:
        fmul dword ptr [esp+0Ch]
    L_0041bec1:
        fstp dword ptr [eax]
    L_0041bec3:
        fmul dword ptr [esp+0Ch]
    L_0041bec7:
        fstp dword ptr [eax+4]
    L_0041beca:
        pop ecx
    L_0041becb:
        ret 8
    }
}

// 0x0041C030..0x0041C091: ScoreObject_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreObject_Initialize_0041c030() {
    __asm {
    L_0041c030:
        mov dword ptr [edx],46DAB0h
    L_0041c036:
        and dword ptr [edx+20h],0FFFFFFFEh
    L_0041c03a:
        lea eax,[edx+68h]
    L_0041c03d:
        mov ecx,12h
    L_0041c042:
        push edi
    L_0041c043:
        and dword ptr [eax],0FFFFFFFEh
    L_0041c046:
        add eax,34h
    L_0041c049:
        dec ecx
    L_0041c04a:
        jne short L_0041c043
    L_0041c04c:
        and dword ptr [edx+420h],0FFFFFFFEh
    L_0041c053:
        xor eax,eax
    L_0041c055:
        mov ecx,109h
    L_0041c05a:
        mov edi,edx
    L_0041c05c:
        rep stosd
    L_0041c05e:
        mov eax,dword ptr [edx+20h]
    L_0041c061:
        xor ecx,ecx
    L_0041c063:
        test al,1
    L_0041c065:
        pop edi
    L_0041c066:
        jne short L_0041c082
    L_0041c068:
        or eax,1
    L_0041c06b:
        mov dword ptr [edx+14h],ecx
    L_0041c06e:
        mov dword ptr [edx+10h],0FFF0BDC1h
    L_0041c075:
        mov dword ptr [edx+18h],ecx
    L_0041c078:
        mov dword ptr [edx+1Ch],476F78h
    L_0041c07f:
        mov dword ptr [edx+20h],eax
    L_0041c082:
        mov dword ptr [edx+14h],ecx
    L_0041c085:
        mov dword ptr [edx+18h],ecx
    L_0041c088:
        mov dword ptr [edx+10h],0FFFFFFFFh
    L_0041c08f:
        mov eax,edx
    L_0041c091:
        ret
    }
}

// 0x0041C1C0..0x0041C282: ScoreExtendedObject_DestroyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreExtendedObject_DestroyRetail_0041c1c0() {
    __asm {
    L_0041c1c0:
        mov eax,dword ptr [esp+4]
    L_0041c1c4:
        push ebx
    L_0041c1c5:
        mov ebx,dword ptr [data_004660b0]
    L_0041c1cb:
        push ebp
    L_0041c1cc:
        mov ebp,dword ptr [data_004660b4]
    L_0041c1d2:
        push esi
    L_0041c1d3:
        mov esi,dword ptr [eax+8]
    L_0041c1d6:
        test esi,esi
    L_0041c1d8:
        push edi
    L_0041c1d9:
        mov edi,dword ptr [data_00491be4]
    L_0041c1df:
        je short L_0041c204
    L_0041c1e1:
        push 492274h
    L_0041c1e6:
        call ebx
    L_0041c1e8:
        inc byte ptr [data_0049231c]
    L_0041c1ee:
        mov ecx,esi
    L_0041c1f0:
        mov edx,edi
    L_0041c1f2:
        call asm_Scheduler_Remove_00449f60
    L_0041c1f7:
        push 492274h
    L_0041c1fc:
        call ebp
    L_0041c1fe:
        dec byte ptr [data_0049231c]
    L_0041c204:
        mov ecx,dword ptr [esp+14h]
    L_0041c208:
        mov esi,dword ptr [ecx+0Ch]
    L_0041c20b:
        test esi,esi
    L_0041c20d:
        mov edi,dword ptr [data_00491be4]
    L_0041c213:
        je short L_0041c238
    L_0041c215:
        push 492274h
    L_0041c21a:
        call ebx
    L_0041c21c:
        inc byte ptr [data_0049231c]
    L_0041c222:
        mov ecx,esi
    L_0041c224:
        mov edx,edi
    L_0041c226:
        call asm_Scheduler_Remove_00449f60
    L_0041c22b:
        push 492274h
    L_0041c230:
        call ebp
    L_0041c232:
        dec byte ptr [data_0049231c]
    L_0041c238:
        mov edx,dword ptr [esp+14h]
    L_0041c23c:
        mov esi,dword ptr [edx+18h]
    L_0041c23f:
        test esi,esi
    L_0041c241:
        je short L_0041c272
    L_0041c243:
        mov eax,dword ptr [esi]
    L_0041c245:
        mov edi,dword ptr [esi+8]
    L_0041c248:
        mov ecx,esi
    L_0041c24a:
        call dword ptr [eax+10h]
    L_0041c24d:
        mov ecx,dword ptr [esi+4]
    L_0041c250:
        mov edx,dword ptr [esi+8]
    L_0041c253:
        mov dword ptr [ecx+8],edx
    L_0041c256:
        mov eax,dword ptr [esi+8]
    L_0041c259:
        test eax,eax
    L_0041c25b:
        je short L_0041c263
    L_0041c25d:
        mov ecx,dword ptr [esi+4]
    L_0041c260:
        mov dword ptr [eax+4],ecx
    L_0041c263:
        push esi
    L_0041c264:
        call asm_free_004524a1
    L_0041c269:
        add esp,4
    L_0041c26c:
        test edi,edi
    L_0041c26e:
        mov esi,edi
    L_0041c270:
        jne short L_0041c243
    L_0041c272:
        pop edi
    L_0041c273:
        pop esi
    L_0041c274:
        pop ebp
    L_0041c275:
        mov dword ptr [data_0047781c],0
    L_0041c27f:
        pop ebx
    L_0041c280:
        ret 4
    }
}

// 0x0041C5B0..0x0041C679: ScoreExtendedObject_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreExtendedObject_Initialize_0041c5b0() {
    __asm {
    L_0041c5b0:
        push esi
    L_0041c5b1:
        push edi
    L_0041c5b2:
        mov edx,ebx
    L_0041c5b4:
        call asm_ScoreObject_Initialize_0041c030
    L_0041c5b9:
        mov dword ptr [ebx],46DA60h
    L_0041c5bf:
        lea edx,[ebx+600h]
    L_0041c5c5:
        xor eax,eax
    L_0041c5c7:
        mov esi,0FFFFFFFEh
    L_0041c5cc:
        mov ecx,77h
    L_0041c5d1:
        lea edi,[ebx+424h]
    L_0041c5d7:
        rep stosd
    L_0041c5d9:
        and dword ptr [edx+6Ch],esi
    L_0041c5dc:
        and dword ptr [edx+0B0h],esi
    L_0041c5e2:
        and dword ptr [edx+0FCh],esi
    L_0041c5e8:
        and dword ptr [edx+128h],esi
    L_0041c5ee:
        and dword ptr [edx+174h],esi
    L_0041c5f4:
        and dword ptr [edx+1B0h],esi
    L_0041c5fa:
        and dword ptr [edx+1FCh],esi
    L_0041c600:
        and dword ptr [edx+228h],esi
    L_0041c606:
        and dword ptr [edx+378h],esi
    L_0041c60c:
        xor eax,eax
    L_0041c60e:
        mov edi,edx
    L_0041c610:
        mov ecx,0EBh
    L_0041c615:
        rep stosd
    L_0041c617:
        mov word ptr [edx+384h],0FFFFh
    L_0041c620:
        mov edi,dword ptr [ebx+0A18h]
    L_0041c626:
        lea edx,[ebx+9ACh]
    L_0041c62c:
        and edi,esi
    L_0041c62e:
        mov dword ptr [edx+6Ch],edi
    L_0041c631:
        and dword ptr [edx+0B0h],esi
    L_0041c637:
        and dword ptr [edx+0FCh],esi
    L_0041c63d:
        and dword ptr [edx+128h],esi
    L_0041c643:
        and dword ptr [edx+174h],esi
    L_0041c649:
        and dword ptr [edx+1B0h],esi
    L_0041c64f:
        and dword ptr [edx+1FCh],esi
    L_0041c655:
        and dword ptr [edx+228h],esi
    L_0041c65b:
        and dword ptr [edx+378h],esi
    L_0041c661:
        xor eax,eax
    L_0041c663:
        mov ecx,0EBh
    L_0041c668:
        mov edi,edx
    L_0041c66a:
        rep stosd
    L_0041c66c:
        pop edi
    L_0041c66d:
        mov word ptr [edx+384h],0FFFFh
    L_0041c676:
        mov eax,ebx
    L_0041c678:
        pop esi
    L_0041c679:
        ret
    }
}

// 0x0041C7D0..0x0041C7FB: ?ScoreRecords_MarkEligible@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreRecords_MarkEligible_0041c7d0() {
    __asm {
    L_0041c7d0:
        mov eax,dword ptr [eax+18h]
    L_0041c7d3:
        test eax,eax
    L_0041c7d5:
        je short L_0041c7f9
    L_0041c7d7:
        push ebx
    L_0041c7d8:
        mov edx,1
    L_0041c7dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041c7e0:
        cmp dword ptr [eax+0Ch],edx
    L_0041c7e3:
        mov ecx,dword ptr [eax+8]
    L_0041c7e6:
        je short L_0041c7f2
    L_0041c7e8:
        mov bl,byte ptr [eax+50h]
    L_0041c7eb:
        test bl,bl
    L_0041c7ed:
        jne short L_0041c7f2
    L_0041c7ef:
        mov byte ptr [eax+50h],dl
    L_0041c7f2:
        test ecx,ecx
    L_0041c7f4:
        mov eax,ecx
    L_0041c7f6:
        jne short L_0041c7e0
    L_0041c7f8:
        pop ebx
    L_0041c7f9:
        xor eax,eax
    L_0041c7fb:
        ret
    }
}

// 0x0041C800..0x0041C84B: ?ScoreRecords_CopyVectorAndEvaluate@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreRecords_CopyVectorAndEvaluate_0041c800() {
    __asm {
    L_0041c800:
        mov ecx,dword ptr [eax+18h]
    L_0041c803:
        push esi
    L_0041c804:
        add eax,440h
    L_0041c809:
        mov edx,ebx
    L_0041c80b:
        mov esi,dword ptr [edx]
    L_0041c80d:
        mov dword ptr [eax],esi
    L_0041c80f:
        mov esi,dword ptr [edx+4]
    L_0041c812:
        mov dword ptr [eax+4],esi
    L_0041c815:
        mov edx,dword ptr [edx+8]
    L_0041c818:
        push edi
    L_0041c819:
        xor edi,edi
    L_0041c81b:
        test ecx,ecx
    L_0041c81d:
        mov dword ptr [eax+8],edx
    L_0041c820:
        je short L_0041c845
    L_0041c822:
        push ebp
    L_0041c823:
        mov ebp,dword ptr [esp+10h]
    L_0041c827:
        cmp dword ptr [ecx+0Ch],1
    L_0041c82b:
        mov esi,dword ptr [ecx+8]
    L_0041c82e:
        je short L_0041c83e
    L_0041c830:
        mov edx,dword ptr [esp+14h]
    L_0041c834:
        mov eax,dword ptr [ecx]
    L_0041c836:
        push edx
    L_0041c837:
        push ebp
    L_0041c838:
        push ebx
    L_0041c839:
        call dword ptr [eax+1Ch]
    L_0041c83c:
        add edi,eax
    L_0041c83e:
        test esi,esi
    L_0041c840:
        mov ecx,esi
    L_0041c842:
        jne short L_0041c827
    L_0041c844:
        pop ebp
    L_0041c845:
        mov eax,edi
    L_0041c847:
        pop edi
    L_0041c848:
        pop esi
    L_0041c849:
        ret 8
    }
}

// 0x00426610..0x00426652: ?Entity_AngleToPoint@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_AngleToPoint_00426610() {
    __asm {
    L_00426610:
        fld dword ptr [eax]
    L_00426612:
        fsub dword ptr [ecx+3C0h]
    L_00426618:
        fld dword ptr [eax+4]
    L_0042661b:
        fsub dword ptr [ecx+3C4h]
    L_00426621:
        fld dword ptr [data_00470b04]
    L_00426627:
        fld st(1)
    L_00426629:
        fucompp
    L_0042662b:
        fnstsw ax
    L_0042662d:
        test ah,44h
    L_00426630:
        jp short L_0042664e
    L_00426632:
        fld dword ptr [data_00470b04]
    L_00426638:
        fld st(2)
    L_0042663a:
        fucompp
    L_0042663c:
        fnstsw ax
    L_0042663e:
        test ah,44h
    L_00426641:
        jp short L_0042664e
    L_00426643:
        fstp st(0)
    L_00426645:
        fstp st(0)
    L_00426647:
        fld dword ptr [data_00470b94]
    L_0042664d:
        ret
    L_0042664e:
        fxch
    L_00426650:
        fpatan
    L_00426652:
        ret
    }
}

// 0x00426660..0x004266A2: ?Entity_AngleFromPoint@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_AngleFromPoint_00426660() {
    __asm {
    L_00426660:
        fld dword ptr [ecx+3C0h]
    L_00426666:
        fsub dword ptr [eax]
    L_00426668:
        fld dword ptr [ecx+3C4h]
    L_0042666e:
        fsub dword ptr [eax+4]
    L_00426671:
        fld dword ptr [data_00470b04]
    L_00426677:
        fld st(1)
    L_00426679:
        fucompp
    L_0042667b:
        fnstsw ax
    L_0042667d:
        test ah,44h
    L_00426680:
        jp short L_0042669e
    L_00426682:
        fld dword ptr [data_00470b04]
    L_00426688:
        fld st(2)
    L_0042668a:
        fucompp
    L_0042668c:
        fnstsw ax
    L_0042668e:
        test ah,44h
    L_00426691:
        jp short L_0042669e
    L_00426693:
        fstp st(0)
    L_00426695:
        fstp st(0)
    L_00426697:
        fld dword ptr [data_00470b94]
    L_0042669d:
        ret
    L_0042669e:
        fxch
    L_004266a0:
        fpatan
    L_004266a2:
        ret
    }
}

// 0x0044A4E0..0x0044A5E7: Input_PollJoystickButtons
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_PollJoystickButtons_0044a4e0() {
    __asm {
    L_0044a4e0:
        sub esp,148h
    L_0044a4e6:
        mov eax,dword ptr [data_00473660]
    L_0044a4eb:
        xor eax,esp
    L_0044a4ed:
        push ebx
    L_0044a4ee:
        mov dword ptr [esp+148h],eax
    L_0044a4f5:
        push edi
    L_0044a4f6:
        mov ebx,ecx
    L_0044a4f8:
        xor eax,eax
    L_0044a4fa:
        mov ecx,20h
    L_0044a4ff:
        mov edi,497BB0h
    L_0044a504:
        rep stosd
    L_0044a506:
        mov eax,dword ptr [data_00491ff4]
    L_0044a50b:
        test ah,4
    L_0044a50e:
        jne short L_0044a55d
    L_0044a510:
        xor eax,eax
    L_0044a512:
        mov ecx,0Dh
    L_0044a517:
        lea edi,[esp+8]
    L_0044a51b:
        rep stosd
    L_0044a51d:
        lea eax,[esp+8]
    L_0044a521:
        push eax
    L_0044a522:
        push 0
    L_0044a524:
        mov dword ptr [esp+10h],34h
    L_0044a52c:
        mov dword ptr [esp+14h],0FFh
    L_0044a534:
        call dword ptr [data_00466280]
    L_0044a53a:
        test eax,eax
    L_0044a53c:
        jne asm_target_0044a5cc
    L_0044a542:
        mov ecx,dword ptr [esp+28h]
    L_0044a546:
        mov dl,80h
    L_0044a548:
        test cl,1
    L_0044a54b:
        je short L_0044a553
    L_0044a54d:
        mov byte ptr [eax+497BB0h],dl
    L_0044a553:
        inc eax
    L_0044a554:
        shr ecx,1
    L_0044a556:
        cmp eax,20h
    L_0044a559:
        jb short L_0044a548
    L_0044a55b:
        jmp short L_0044a5cc
    L_0044a55d:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a564:
        mov ecx,dword ptr [eax]
    L_0044a566:
        push esi
    L_0044a567:
        push eax
    L_0044a568:
        call dword ptr [ecx+64h]
    L_0044a56b:
        test eax,eax
    L_0044a56d:
        jge short L_0044a5a4
    L_0044a56f:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a576:
        mov edx,dword ptr [eax]
    L_0044a578:
        push eax
    L_0044a579:
        xor esi,esi
    L_0044a57b:
        call dword ptr [edx+1Ch]
    L_0044a57e:
        cmp eax,8007001Eh
    L_0044a583:
        jne short L_0044a5cb
    L_0044a585:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a58c:
        mov ecx,dword ptr [eax]
    L_0044a58e:
        push eax
    L_0044a58f:
        call dword ptr [ecx+1Ch]
    L_0044a592:
        inc esi
    L_0044a593:
        cmp esi,190h
    L_0044a599:
        jge short L_0044a5cb
    L_0044a59b:
        cmp eax,8007001Eh
    L_0044a5a0:
        je short L_0044a585
    L_0044a5a2:
        jmp short L_0044a5cb
    L_0044a5a4:
        mov ebx,dword ptr [ebx*4+491C3Ch]
    L_0044a5ab:
        mov edx,dword ptr [ebx]
    L_0044a5ad:
        lea eax,[esp+40h]
    L_0044a5b1:
        push eax
    L_0044a5b2:
        push 110h
    L_0044a5b7:
        push ebx
    L_0044a5b8:
        call dword ptr [edx+24h]
    L_0044a5bb:
        mov ecx,20h
    L_0044a5c0:
        lea esi,[esp+70h]
    L_0044a5c4:
        mov edi,497BB0h
    L_0044a5c9:
        rep movsd
    L_0044a5cb:
        pop esi
    L_0044a5cc:
        mov ecx,dword ptr [esp+14Ch]
    L_0044a5d3:
        pop edi
    L_0044a5d4:
        pop ebx
    L_0044a5d5:
        xor ecx,esp
    L_0044a5d7:
        mov eax,497BB0h
    L_0044a5dc:
        call asm_security_check_cookie_00458ea5
    L_0044a5e1:
        add esp,148h
    L_0044a5e7:
        ret
    }
}

// 0x0044B010..0x0044B076: ?Input_UpdateKeyboardState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_UpdateKeyboardState_0044b010() {
    __asm {
    L_0044b010:
        push edi
    L_0044b011:
        xor eax,eax
    L_0044b013:
        mov ecx,40h
    L_0044b018:
        mov edi,edx
    L_0044b01a:
        rep stosd
    L_0044b01c:
        mov eax,dword ptr [data_004924fc]
    L_0044b021:
        test eax,eax
    L_0044b023:
        pop edi
    L_0044b024:
        je short L_0044b037
    L_0044b026:
        mov eax,dword ptr [data_00491ff4]
    L_0044b02b:
        test ah,2
    L_0044b02e:
        push edx
    L_0044b02f:
        jne short L_0044b03a
    L_0044b031:
        call dword ptr [data_00466208]
    L_0044b037:
        xor eax,eax
    L_0044b039:
        ret
    L_0044b03a:
        mov eax,dword ptr [data_00491c38]
    L_0044b03f:
        mov ecx,dword ptr [eax]
    L_0044b041:
        push 100h
    L_0044b046:
        push eax
    L_0044b047:
        call dword ptr [ecx+24h]
    L_0044b04a:
        cmp eax,8007001Eh
    L_0044b04f:
        jne short L_0044b062
    L_0044b051:
        mov eax,dword ptr [data_00491c38]
    L_0044b056:
        mov edx,dword ptr [eax]
    L_0044b058:
        push eax
    L_0044b059:
        call dword ptr [edx+1Ch]
    L_0044b05c:
        mov eax,1
    L_0044b061:
        ret
    L_0044b062:
        test eax,eax
    L_0044b064:
        je short L_0044b071
    L_0044b066:
        mov eax,dword ptr [data_00491c38]
    L_0044b06b:
        mov ecx,dword ptr [eax]
    L_0044b06d:
        push eax
    L_0044b06e:
        call dword ptr [ecx+1Ch]
    L_0044b071:
        mov eax,1
    L_0044b076:
        ret
    }
}

// 0x0044B080..0x0044B0CA: ?Input_NormalizeKeyboardState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_NormalizeKeyboardState_0044b080() {
    __asm {
    L_0044b080:
        sub esp,104h
    L_0044b086:
        mov eax,dword ptr [data_00473660]
    L_0044b08b:
        xor eax,esp
    L_0044b08d:
        mov dword ptr [esp+100h],eax
    L_0044b094:
        lea eax,[esp]
    L_0044b097:
        push eax
    L_0044b098:
        call dword ptr [data_00466208]
    L_0044b09e:
        xor eax,eax
    L_0044b0a0:
        and byte ptr [esp+eax],7Fh
    L_0044b0a4:
        inc eax
    L_0044b0a5:
        cmp eax,100h
    L_0044b0aa:
        jl short L_0044b0a0
    L_0044b0ac:
        lea ecx,[esp]
    L_0044b0af:
        push ecx
    L_0044b0b0:
        call dword ptr [data_00466204]
    L_0044b0b6:
        mov ecx,dword ptr [esp+100h]
    L_0044b0bd:
        xor ecx,esp
    L_0044b0bf:
        call asm_security_check_cookie_00458ea5
    L_0044b0c4:
        add esp,104h
    L_0044b0ca:
        ret
    }
}

// 0x0044BE20..0x0044BE61: ?Score_InputHistorySave@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_InputHistorySave_0044be20() {
    __asm {
    L_0044be20:
        mov ecx,dword ptr [eax+8Ch]
    L_0044be26:
        mov edx,dword ptr [eax]
    L_0044be28:
        mov dword ptr [eax+ecx*4+0Ch],edx
    L_0044be2c:
        mov ecx,dword ptr [eax+8Ch]
    L_0044be32:
        mov edx,dword ptr [eax+8]
    L_0044be35:
        mov dword ptr [eax+ecx*4+4Ch],edx
    L_0044be39:
        mov edx,dword ptr [eax+8Ch]
    L_0044be3f:
        inc edx
    L_0044be40:
        mov ecx,edx
    L_0044be42:
        cmp ecx,10h
    L_0044be45:
        mov dword ptr [eax+8Ch],edx
    L_0044be4b:
        mov dword ptr [eax+0D4h],0
    L_0044be55:
        jl short L_0044be61
    L_0044be57:
        mov dword ptr [eax+8Ch],0Fh
    L_0044be61:
        ret
    }
}

// 0x0044BE70..0x0044BE9E: ?Score_InputHistoryStep@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_InputHistoryStep_0044be70() {
    __asm {
    L_0044be70:
        dec dword ptr [eax+8Ch]
    L_0044be76:
        mov edx,0
    L_0044be7b:
        jns short L_0044be83
    L_0044be7d:
        mov dword ptr [eax+8Ch],edx
    L_0044be83:
        mov ecx,dword ptr [eax+8Ch]
    L_0044be89:
        push esi
    L_0044be8a:
        mov esi,dword ptr [eax+ecx*4+0Ch]
    L_0044be8e:
        mov dword ptr [eax],esi
    L_0044be90:
        mov ecx,dword ptr [eax+ecx*4+4Ch]
    L_0044be94:
        mov dword ptr [eax+8],ecx
    L_0044be97:
        mov dword ptr [eax+0D4h],edx
    L_0044be9d:
        pop esi
    L_0044be9e:
        ret
    }
}
