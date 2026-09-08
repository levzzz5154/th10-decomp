#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_StopAtFrame2_0040c480() {
    __asm {
    L_0040c480:
        mov eax,dword ptr [eax]
    L_0040c482:
        mov edx,dword ptr [data_00491c10]
    L_0040c488:
        push eax
    L_0040c489:
        call asm_AnimationManager_Find_004491c0
    L_0040c48e:
        test eax,eax
    L_0040c490:
        je short L_0040c4c0
    L_0040c492:
        mov edx,dword ptr [eax+18h]
    L_0040c495:
        test edx,edx
    L_0040c497:
        mov ecx,2
    L_0040c49c:
        mov word ptr [eax+304h],cx
    L_0040c4a3:
        jne short L_0040c4c0
    L_0040c4a5:
        mov eax,dword ptr [eax+14h]
    L_0040c4a8:
        test eax,eax
    L_0040c4aa:
        je short L_0040c4c0
    L_0040c4ac:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040c4b0:
        mov edx,dword ptr [eax]
    L_0040c4b2:
        mov word ptr [edx+304h],cx
    L_0040c4b9:
        mov eax,dword ptr [eax+4]
    L_0040c4bc:
        test eax,eax
    L_0040c4be:
        jne short L_0040c4b0
    L_0040c4c0:
        ret
    }
}

// 0x0040C4D0..0x0040C510: ?AnimationManager_StopAtFrame3@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_StopAtFrame3_0040c4d0() {
    __asm {
    L_0040c4d0:
        mov eax,dword ptr [eax]
    L_0040c4d2:
        mov edx,dword ptr [data_00491c10]
    L_0040c4d8:
        push eax
    L_0040c4d9:
        call asm_AnimationManager_Find_004491c0
    L_0040c4de:
        test eax,eax
    L_0040c4e0:
        je short L_0040c510
    L_0040c4e2:
        mov edx,dword ptr [eax+18h]
    L_0040c4e5:
        test edx,edx
    L_0040c4e7:
        mov ecx,3
    L_0040c4ec:
        mov word ptr [eax+304h],cx
    L_0040c4f3:
        jne short L_0040c510
    L_0040c4f5:
        mov eax,dword ptr [eax+14h]
    L_0040c4f8:
        test eax,eax
    L_0040c4fa:
        je short L_0040c510
    L_0040c4fc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040c500:
        mov edx,dword ptr [eax]
    L_0040c502:
        mov word ptr [edx+304h],cx
    L_0040c509:
        mov eax,dword ptr [eax+4]
    L_0040c50c:
        test eax,eax
    L_0040c50e:
        jne short L_0040c500
    L_0040c510:
        ret
    }
}

// 0x0043DC90..0x0043DD0A: ?AnimationManager_QueueResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_QueueResource_0043dc90() {
    __asm {
    L_0043dc90:
        push ebx
    L_0043dc91:
        movsx ebx,word ptr [edi*8+4749CEh]
    L_0043dc99:
        push ebp
    L_0043dc9a:
        mov ebp,dword ptr [esp+0Ch]
    L_0043dc9e:
        push esi
    L_0043dc9f:
        xor eax,eax
    L_0043dca1:
        lea edx,[ecx+620h]
    L_0043dca7:
        mov esi,dword ptr [edx]
    L_0043dca9:
        test esi,esi
    L_0043dcab:
        jl short L_0043dcdf
    L_0043dcad:
        cmp esi,edi
    L_0043dcaf:
        je short L_0043dcc0
    L_0043dcb1:
        inc eax
    L_0043dcb2:
        add edx,4
    L_0043dcb5:
        cmp eax,0Ch
    L_0043dcb8:
        jl short L_0043dca7
    L_0043dcba:
        pop esi
    L_0043dcbb:
        pop ebp
    L_0043dcbc:
        pop ebx
    L_0043dcbd:
        ret 4
    L_0043dcc0:
        mov edx,dword ptr [ecx+eax*4+650h]
    L_0043dcc7:
        cmp edx,80h
    L_0043dccd:
        jge short L_0043dd05
    L_0043dccf:
        mov esi,eax
    L_0043dcd1:
        shl esi,7
    L_0043dcd4:
        add esi,edx
    L_0043dcd6:
        mov dword ptr [ecx+esi*4+680h],ebp
    L_0043dcdd:
        jmp short L_0043dcfe
    L_0043dcdf:
        cmp eax,0Ch
    L_0043dce2:
        jge short L_0043dd05
    L_0043dce4:
        mov edx,eax
    L_0043dce6:
        mov dword ptr [ecx+eax*4+620h],edi
    L_0043dced:
        shl edx,9
    L_0043dcf0:
        mov dword ptr [ecx+edi*4+408h],ebx
    L_0043dcf7:
        mov dword ptr [edx+ecx+680h],ebp
    L_0043dcfe:
        inc dword ptr [ecx+eax*4+650h]
    L_0043dd05:
        pop esi
    L_0043dd06:
        pop ebp
    L_0043dd07:
        pop ebx
    L_0043dd08:
        ret 4
    }
}

// 0x0043E460..0x0043E46C: ?AnimationManager_RegisterResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterResource_0043e460() {
    __asm {
    L_0043e460:
        push esi
    L_0043e461:
        mov esi,eax
    L_0043e463:
        xor eax,eax
    L_0043e465:
        lea ecx,[esi+1F88h]
    L_0043e46b:
        TH10_REL8(0xeb, 0x0043e46b, VA_asm_AnimationManager_RegisterResource_part_0043e470)
    }
}

// 0x0043E470..0x0043E4C7: ?AnimationManager_RegisterResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterResource_part_0043e470() {
    __asm {
    L_0043e470:
        cmp dword ptr [ecx],0
    L_0043e473:
        je short L_0043e485
    L_0043e475:
        inc eax
    L_0043e476:
        add ecx,10Ch
    L_0043e47c:
        cmp eax,1Fh
    L_0043e47f:
        jl short L_0043e470
    L_0043e481:
        pop esi
    L_0043e482:
        ret 8
    L_0043e485:
        imul eax,10Ch
    L_0043e48b:
        lea ecx,[eax+esi]
    L_0043e48e:
        mov eax,dword ptr [esp+8]
    L_0043e492:
        mov dword ptr [ecx+1F88h],eax
    L_0043e498:
        mov eax,dword ptr [esp+0Ch]
    L_0043e49c:
        lea esi,[ecx+1F94h]
    L_0043e4a2:
        mov dword ptr [ecx+1F8Ch],eax
    L_0043e4a8:
        mov eax,edx
    L_0043e4aa:
        sub esi,edx
    L_0043e4ac:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043e4b0:
        mov dl,byte ptr [eax]
    L_0043e4b2:
        mov byte ptr [esi+eax],dl
    L_0043e4b5:
        inc eax
    L_0043e4b6:
        test dl,dl
    L_0043e4b8:
        jne short L_0043e4b0
    L_0043e4ba:
        mov dword ptr [ecx+1F90h],0
    L_0043e4c4:
        pop esi
    L_0043e4c5:
        ret 8
    }
}

// 0x0043E710..0x0043E7DA: ?AnimationObject_LoadScript@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_LoadScript_0043e710() {
    __asm {
    L_0043e710:
        push ebp
    L_0043e711:
        push esi
    L_0043e712:
        mov esi,ecx
    L_0043e714:
        push edi
    L_0043e715:
        mov edi,eax
    L_0043e717:
        mov eax,dword ptr [esi+11Ch]
    L_0043e71d:
        mov ecx,dword ptr [eax+ebx*4]
    L_0043e720:
        xor ebp,ebp
    L_0043e722:
        cmp ecx,ebp
    L_0043e724:
        je asm_target_0043e7ce
    L_0043e72a:
        cmp dword ptr [esi+124h],ebp
    L_0043e730:
        jne asm_target_0043e7ce
    L_0043e736:
        mov edx,edi
    L_0043e738:
        call asm_InitializeEntity_00401de0
    L_0043e73d:
        mov edx,dword ptr [edi+35Ch]
    L_0043e743:
        mov word ptr [edi+38Ah],bx
    L_0043e74a:
        mov cx,word ptr [esi]
    L_0043e74d:
        and edx,0FFFFF9FFh
    L_0043e753:
        mov word ptr [edi+386h],cx
    L_0043e75a:
        mov dword ptr [edi+308h],esi
    L_0043e760:
        mov dword ptr [edi+35Ch],edx
    L_0043e766:
        mov edx,dword ptr [esi+11Ch]
    L_0043e76c:
        mov eax,dword ptr [edx+ebx*4]
    L_0043e76f:
        mov dword ptr [edi+38Ch],eax
    L_0043e775:
        mov dword ptr [edi+390h],eax
    L_0043e77b:
        mov eax,dword ptr [edi+6Ch]
    L_0043e77e:
        test al,1
    L_0043e780:
        jne short L_0043e79c
    L_0043e782:
        or eax,1
    L_0043e785:
        mov dword ptr [edi+60h],ebp
    L_0043e788:
        mov dword ptr [edi+5Ch],0FFF0BDC1h
    L_0043e78f:
        mov dword ptr [edi+64h],ebp
    L_0043e792:
        mov dword ptr [edi+68h],476F78h
    L_0043e799:
        mov dword ptr [edi+6Ch],eax
    L_0043e79c:
        mov dword ptr [edi+60h],ebp
    L_0043e79f:
        mov dword ptr [edi+64h],ebp
    L_0043e7a2:
        mov dword ptr [edi+5Ch],0FFFFFFFFh
    L_0043e7a9:
        mov esi,dword ptr [edi+35Ch]
    L_0043e7af:
        and esi,0FFFFFFFEh
    L_0043e7b2:
        push edi
    L_0043e7b3:
        mov dword ptr [edi+35Ch],esi
    L_0043e7b9:
        call asm_FUN_0043ee30_0043ee30
    L_0043e7be:
        mov eax,dword ptr [data_00491c10]
    L_0043e7c3:
        mov ecx,dword ptr [eax+4Ch]
    L_0043e7c6:
        pop edi
    L_0043e7c7:
        inc ecx
    L_0043e7c8:
        pop esi
    L_0043e7c9:
        mov dword ptr [eax+4Ch],ecx
    L_0043e7cc:
        pop ebp
    L_0043e7cd:
        ret
    L_0043e7ce:
        mov ecx,0EBh
    L_0043e7d3:
        xor eax,eax
    L_0043e7d5:
        rep stosd
    L_0043e7d7:
        pop edi
    L_0043e7d8:
        pop esi
    L_0043e7d9:
        pop ebp
    L_0043e7da:
        ret
    }
}

// 0x0043E7E0..0x0043E8A1: ?AnimationObject_LoadScriptPreservingState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_LoadScriptPreservingState_0043e7e0() {
    __asm {
    L_0043e7e0:
        push ebx
    L_0043e7e1:
        push esi
    L_0043e7e2:
        mov esi,dword ptr [eax+11Ch]
    L_0043e7e8:
        mov ebx,dword ptr [esi+ecx*4]
    L_0043e7eb:
        push edi
    L_0043e7ec:
        mov edi,edx
    L_0043e7ee:
        xor edx,edx
    L_0043e7f0:
        cmp ebx,edx
    L_0043e7f2:
        je asm_target_0043e895
    L_0043e7f8:
        cmp dword ptr [eax+124h],edx
    L_0043e7fe:
        jne asm_target_0043e895
    L_0043e804:
        mov word ptr [edi+38Ah],cx
    L_0043e80b:
        mov si,word ptr [eax]
    L_0043e80e:
        mov word ptr [edi+386h],si
    L_0043e815:
        mov esi,dword ptr [edi+35Ch]
    L_0043e81b:
        and esi,0FFFFF9FFh
    L_0043e821:
        mov dword ptr [edi+308h],eax
    L_0043e827:
        mov dword ptr [edi+35Ch],esi
    L_0043e82d:
        mov eax,dword ptr [eax+11Ch]
    L_0043e833:
        mov eax,dword ptr [eax+ecx*4]
    L_0043e836:
        mov dword ptr [edi+38Ch],eax
    L_0043e83c:
        mov dword ptr [edi+390h],eax
    L_0043e842:
        mov eax,dword ptr [edi+6Ch]
    L_0043e845:
        test al,1
    L_0043e847:
        jne short L_0043e863
    L_0043e849:
        or eax,1
    L_0043e84c:
        mov dword ptr [edi+60h],edx
    L_0043e84f:
        mov dword ptr [edi+5Ch],0FFF0BDC1h
    L_0043e856:
        mov dword ptr [edi+64h],edx
    L_0043e859:
        mov dword ptr [edi+68h],476F78h
    L_0043e860:
        mov dword ptr [edi+6Ch],eax
    L_0043e863:
        mov dword ptr [edi+60h],edx
    L_0043e866:
        mov dword ptr [edi+64h],edx
    L_0043e869:
        mov dword ptr [edi+5Ch],0FFFFFFFFh
    L_0043e870:
        mov esi,dword ptr [edi+35Ch]
    L_0043e876:
        and esi,0FFFFFFFEh
    L_0043e879:
        push edi
    L_0043e87a:
        mov dword ptr [edi+35Ch],esi
    L_0043e880:
        call asm_FUN_0043ee30_0043ee30
    L_0043e885:
        mov eax,dword ptr [data_00491c10]
    L_0043e88a:
        mov ecx,dword ptr [eax+4Ch]
    L_0043e88d:
        pop edi
    L_0043e88e:
        inc ecx
    L_0043e88f:
        pop esi
    L_0043e890:
        mov dword ptr [eax+4Ch],ecx
    L_0043e893:
        pop ebx
    L_0043e894:
        ret
    L_0043e895:
        mov ecx,0EBh
    L_0043e89a:
        xor eax,eax
    L_0043e89c:
        rep stosd
    L_0043e89e:
        pop edi
    L_0043e89f:
        pop esi
    L_0043e8a0:
        pop ebx
    L_0043e8a1:
        ret
    }
}

// 0x0043E8B0..0x0043E9CE: ?AnimationObject_ChangeScript@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ChangeScript_0043e8b0() {
    __asm {
    L_0043e8b0:
        push esi
    L_0043e8b1:
        push edi
    L_0043e8b2:
        mov edi,ecx
    L_0043e8b4:
        mov ecx,dword ptr [edx+11Ch]
    L_0043e8ba:
        mov esi,dword ptr [ecx+edi*4]
    L_0043e8bd:
        xor ecx,ecx
    L_0043e8bf:
        cmp esi,ecx
    L_0043e8c1:
        je asm_target_0043e9cc
    L_0043e8c7:
        push ebp
    L_0043e8c8:
        cmp dword ptr [edx+124h],ecx
    L_0043e8ce:
        jne asm_target_0043e9cb
    L_0043e8d4:
        mov word ptr [eax+38Ah],di
    L_0043e8db:
        mov edi,dword ptr [eax+35Ch]
    L_0043e8e1:
        test edi,200h
    L_0043e8e7:
        mov dword ptr [eax+308h],edx
    L_0043e8ed:
        je short L_0043e90a
    L_0043e8ef:
        fld dword ptr [eax+3Ch]
    L_0043e8f2:
        or edi,8
    L_0043e8f5:
        fmul dword ptr [data_00470b60]
    L_0043e8fb:
        xor edi,200h
    L_0043e901:
        mov dword ptr [eax+35Ch],edi
    L_0043e907:
        fstp dword ptr [eax+3Ch]
    L_0043e90a:
        mov word ptr [eax+35Ch],7
    L_0043e913:
        mov dword ptr [eax+2FCh],0FFFFFFFFh
    L_0043e91d:
        mov dword ptr [eax+60h],ecx
    L_0043e920:
        mov dword ptr [eax+64h],ecx
    L_0043e923:
        mov edi,0FFF0BDC1h
    L_0043e928:
        mov dword ptr [eax+5Ch],edi
    L_0043e92b:
        mov dword ptr [eax+0B4h],ecx
    L_0043e931:
        mov dword ptr [eax+100h],ecx
    L_0043e937:
        mov dword ptr [eax+12Ch],ecx
    L_0043e93d:
        mov dword ptr [eax+178h],ecx
    L_0043e943:
        mov dword ptr [eax+1B4h],ecx
    L_0043e949:
        mov dword ptr [eax+200h],ecx
    L_0043e94f:
        mov dword ptr [eax+22Ch],ecx
    L_0043e955:
        mov bp,word ptr [edx]
    L_0043e958:
        mov word ptr [eax+386h],bp
    L_0043e95f:
        mov ebp,dword ptr [eax+35Ch]
    L_0043e965:
        and ebp,0FFFFF9FFh
    L_0043e96b:
        mov dword ptr [eax+308h],edx
    L_0043e971:
        mov dword ptr [eax+35Ch],ebp
    L_0043e977:
        mov dword ptr [eax+38Ch],esi
    L_0043e97d:
        mov dword ptr [eax+390h],esi
    L_0043e983:
        mov edx,dword ptr [eax+6Ch]
    L_0043e986:
        test dl,1
    L_0043e989:
        jne short L_0043e9a1
    L_0043e98b:
        or edx,1
    L_0043e98e:
        mov dword ptr [eax+60h],ecx
    L_0043e991:
        mov dword ptr [eax+5Ch],edi
    L_0043e994:
        mov dword ptr [eax+64h],ecx
    L_0043e997:
        mov dword ptr [eax+68h],476F78h
    L_0043e99e:
        mov dword ptr [eax+6Ch],edx
    L_0043e9a1:
        mov dword ptr [eax+60h],ecx
    L_0043e9a4:
        mov dword ptr [eax+64h],ecx
    L_0043e9a7:
        mov dword ptr [eax+5Ch],0FFFFFFFFh
    L_0043e9ae:
        mov esi,dword ptr [eax+35Ch]
    L_0043e9b4:
        and esi,0FFFFFFFEh
    L_0043e9b7:
        push eax
    L_0043e9b8:
        mov dword ptr [eax+35Ch],esi
    L_0043e9be:
        call asm_FUN_0043ee30_0043ee30
    L_0043e9c3:
        mov eax,dword ptr [data_00491c10]
    L_0043e9c8:
        inc dword ptr [eax+4Ch]
    L_0043e9cb:
        pop ebp
    L_0043e9cc:
        pop edi
    L_0043e9cd:
        pop esi
    L_0043e9ce:
        ret
    }
}

// 0x0043EC70..0x0043ECD7: ?AnimationObject_ReadIntegerVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ReadIntegerVariable_0043ec70() {
    __asm {
    L_0043ec70:
        lea edx,[eax-2710h]
    L_0043ec76:
        cmp edx,9
    L_0043ec79:
        ja short L_0043ecd7
    L_0043ec7b:
        jmp dword ptr [edx*4+43ECD8h]
    L_0043ec82:
        mov eax,dword ptr [ecx+30Ch]
    L_0043ec88:
        ret
    L_0043ec89:
        mov eax,dword ptr [ecx+310h]
    L_0043ec8f:
        ret
    L_0043ec90:
        mov eax,dword ptr [ecx+314h]
    L_0043ec96:
        ret
    L_0043ec97:
        mov eax,dword ptr [ecx+318h]
    L_0043ec9d:
        ret
    L_0043ec9e:
        fld dword ptr [ecx+31Ch]
    L_0043eca4:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043eca9:
        fld dword ptr [ecx+320h]
    L_0043ecaf:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecb4:
        fld dword ptr [ecx+324h]
    L_0043ecba:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecbf:
        fld dword ptr [ecx+328h]
    L_0043ecc5:
        jmp asm_FUN_00463b2c_00463b2c
    L_0043ecca:
        mov eax,dword ptr [ecx+32Ch]
    L_0043ecd0:
        ret
    L_0043ecd1:
        mov eax,dword ptr [ecx+330h]
    L_0043ecd7:
        ret
    }
}

// 0x0043ED00..0x0043ED6B: ?AnimationObject_ResolveFloatVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ResolveFloatVariable_0043ed00() {
    __asm {
    L_0043ed00:
        mov eax,1
    L_0043ed05:
        shl eax,cl
    L_0043ed07:
        movzx ecx,word ptr [esp+4]
    L_0043ed0c:
        test eax,ecx
    L_0043ed0e:
        je short L_0043ed67
    L_0043ed10:
        fld dword ptr [edi]
    L_0043ed12:
        call asm_FUN_00463b2c_00463b2c
    L_0043ed17:
        add eax,0FFFFD8ECh
    L_0043ed1c:
        cmp eax,0Bh
    L_0043ed1f:
        ja short L_0043ed67
    L_0043ed21:
        jmp dword ptr [eax*4+43ED6Ch]
    L_0043ed28:
        lea eax,[esi+31Ch]
    L_0043ed2e:
        ret 4
    L_0043ed31:
        lea eax,[esi+320h]
    L_0043ed37:
        ret 4
    L_0043ed3a:
        lea eax,[esi+324h]
    L_0043ed40:
        ret 4
    L_0043ed43:
        lea eax,[esi+328h]
    L_0043ed49:
        ret 4
    L_0043ed4c:
        lea eax,[esi+334h]
    L_0043ed52:
        ret 4
    L_0043ed55:
        lea eax,[esi+338h]
    L_0043ed5b:
        ret 4
    L_0043ed5e:
        lea eax,[esi+33Ch]
    L_0043ed64:
        ret 4
    L_0043ed67:
        mov eax,edi
    L_0043ed69:
        ret 4
    }
}

// 0x0043EDA0..0x0043EDFB: ?AnimationObject_ResolveIntegerVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationObject_ResolveIntegerVariable_0043eda0() {
    __asm {
    L_0043eda0:
        push esi
    L_0043eda1:
        mov esi,1
    L_0043eda6:
        shl esi,cl
    L_0043eda8:
        movzx ecx,word ptr [esp+8]
    L_0043edad:
        test esi,ecx
    L_0043edaf:
        pop esi
    L_0043edb0:
        je short L_0043edf9
    L_0043edb2:
        mov ecx,dword ptr [eax]
    L_0043edb4:
        add ecx,0FFFFD8F0h
    L_0043edba:
        cmp ecx,9
    L_0043edbd:
        ja short L_0043edf9
    L_0043edbf:
        jmp dword ptr [ecx*4+43EDFCh]
    L_0043edc6:
        lea eax,[edx+30Ch]
    L_0043edcc:
        ret 4
    L_0043edcf:
        lea eax,[edx+310h]
    L_0043edd5:
        ret 4
    L_0043edd8:
        lea eax,[edx+314h]
    L_0043edde:
        ret 4
    L_0043ede1:
        lea eax,[edx+318h]
    L_0043ede7:
        ret 4
    L_0043edea:
        lea eax,[edx+32Ch]
    L_0043edf0:
        ret 4
    L_0043edf3:
        lea eax,[edx+330h]
    L_0043edf9:
        ret 4
    }
}

// 0x004423C0..0x004423D8: ?AnimationColor_MultiplyChannel@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationColor_MultiplyChannel_004423c0() {
    __asm {
    L_004423c0:
        movzx eax,al
    L_004423c3:
        movzx ecx,cl
    L_004423c6:
        imul eax,ecx
    L_004423c9:
        shr eax,7
    L_004423cc:
        cmp eax,100h
    L_004423d1:
        jb short L_004423d8
    L_004423d3:
        mov eax,0FFh
    L_004423d8:
        ret
    }
}

// 0x00446220..0x004462ED: FUN_00446220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446220_00446220() {
    __asm {
    L_00446220:
        mov eax,dword ptr fs:[0]
    L_00446226:
        push 0FFFFFFFFh
    L_00446228:
        push 465225h
    L_0044622d:
        push eax
    L_0044622e:
        mov dword ptr fs:[0],esp
    L_00446235:
        push ebx
    L_00446236:
        push esi
    L_00446237:
        push edi
    L_00446238:
        mov edi,dword ptr [esp+1Ch]
    L_0044623c:
        mov dword ptr [esp+14h],2
    L_00446244:
        mov eax,dword ptr [edi+72DAD4h]
    L_0044624a:
        test eax,eax
    L_0044624c:
        je short L_00446260
    L_0044624e:
        mov edi,edi
    L_00446250:
        mov esi,dword ptr [eax]
    L_00446252:
        mov ebx,dword ptr [eax+4]
    L_00446255:
        call asm_FUN_00448bb0_00448bb0
    L_0044625a:
        test ebx,ebx
    L_0044625c:
        mov eax,ebx
    L_0044625e:
        jne short L_00446250
    L_00446260:
        mov eax,dword ptr [edi+72DADCh]
    L_00446266:
        test eax,eax
    L_00446268:
        je short L_00446280
    L_0044626a:
        lea ebx,[ebx+force_disp32_zero]
    L_00446270:
        mov esi,dword ptr [eax]
    L_00446272:
        mov ebx,dword ptr [eax+4]
    L_00446275:
        call asm_FUN_00448bb0_00448bb0
    L_0044627a:
        test ebx,ebx
    L_0044627c:
        mov eax,ebx
    L_0044627e:
        jne short L_00446270
    L_00446280:
        push 401FF0h
    L_00446285:
        push 14h
    L_00446287:
        push 3ACh
    L_0044628c:
        lea eax,[edi+72DAE4h]
    L_00446292:
        push eax
    L_00446293:
        mov byte ptr [esp+24h],1
    L_00446298:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0044629d:
        mov eax,dword ptr [edi+3AD488h]
    L_004462a3:
        test eax,eax
    L_004462a5:
        je short L_004462b0
    L_004462a7:
        push eax
    L_004462a8:
        call asm_free_00452422
    L_004462ad:
        add esp,4
    L_004462b0:
        push 401FF0h
    L_004462b5:
        push 1000h
    L_004462ba:
        mov dword ptr [edi+3AD488h],0
    L_004462c4:
        push 3ACh
    L_004462c9:
        add edi,68h
    L_004462cc:
        push edi
    L_004462cd:
        mov dword ptr [esp+24h],0FFFFFFFFh
    L_004462d5:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004462da:
        mov ecx,dword ptr [esp+0Ch]
    L_004462de:
        pop edi
    L_004462df:
        pop esi
    L_004462e0:
        mov dword ptr fs:[0],ecx
    L_004462e7:
        pop ebx
    L_004462e8:
        add esp,0Ch
    L_004462eb:
        ret 4
    }
}

// 0x00447050..0x00447078: ?AnimationTexture_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationTexture_Create_00447050() {
    __asm {
    L_00447050:
        mov eax,dword ptr [esi*4+46F288h]
    L_00447057:
        push edi
    L_00447058:
        push 1
    L_0044705a:
        push eax
    L_0044705b:
        mov eax,dword ptr [data_00491c30]
    L_00447060:
        push 0
    L_00447062:
        push 1
    L_00447064:
        push ecx
    L_00447065:
        push edx
    L_00447066:
        push eax
    L_00447067:
        call asm_D3DXCreateTexture_004521a0
    L_0044706c:
        mov ecx,dword ptr [esi*4+46F2A0h]
    L_00447073:
        mov dword ptr [edi+0Ch],ecx
    L_00447076:
        xor eax,eax
    L_00447078:
        ret
    }
}

// 0x004477D0..0x00447806: ?AnimationManager_ClearResourceSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearResourceSlot_004477d0() {
    __asm {
    L_004477d0:
        test esi,esi
    L_004477d2:
        jl short L_00447806
    L_004477d4:
        cmp esi,21h
    L_004477d7:
        jae short L_00447806
    L_004477d9:
        push edi
    L_004477da:
        mov edi,dword ptr [ebx+esi*4+3AD06Ch]
    L_004477e1:
        test edi,edi
    L_004477e3:
        je short L_00447805
    L_004477e5:
        call asm_FUN_00447810_00447810
    L_004477ea:
        mov eax,dword ptr [ebx+esi*4+3AD06Ch]
    L_004477f1:
        push eax
    L_004477f2:
        call asm_free_004524a1
    L_004477f7:
        add esp,4
    L_004477fa:
        mov dword ptr [ebx+esi*4+3AD06Ch],0
    L_00447805:
        pop edi
    L_00447806:
        ret
    }
}

// 0x00447810..0x00447901: FUN_00447810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447810_00447810() {
    __asm {
    L_00447810:
        push ecx
    L_00447811:
        mov eax,dword ptr [edi+108h]
    L_00447817:
        push ebp
    L_00447818:
        xor ebp,ebp
    L_0044781a:
        cmp eax,ebp
    L_0044781c:
        je asm_target_004478ff
    L_00447822:
        mov eax,dword ptr [data_00491c10]
    L_00447827:
        mov edx,edi
    L_00447829:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0044782e:
        cmp dword ptr [edi+10Ch],ebp
    L_00447834:
        mov dword ptr [esp+4],ebp
    L_00447838:
        jle short L_00447882
    L_0044783a:
        push ebx
    L_0044783b:
        push esi
    L_0044783c:
        xor ebx,ebx
    L_0044783e:
        mov edi,edi
    L_00447840:
        mov esi,dword ptr [edi+120h]
    L_00447846:
        mov eax,dword ptr [esi+ebx]
    L_00447849:
        add esi,ebx
    L_0044784b:
        cmp eax,ebp
    L_0044784d:
        je short L_00447857
    L_0044784f:
        mov ecx,dword ptr [eax]
    L_00447851:
        push eax
    L_00447852:
        call dword ptr [ecx+8]
    L_00447855:
        mov dword ptr [esi],ebp
    L_00447857:
        mov eax,dword ptr [esi+4]
    L_0044785a:
        cmp eax,ebp
    L_0044785c:
        je short L_0044786a
    L_0044785e:
        push eax
    L_0044785f:
        call asm_free_00452422
    L_00447864:
        add esp,4
    L_00447867:
        mov dword ptr [esi+4],ebp
    L_0044786a:
        mov eax,dword ptr [esp+0Ch]
    L_0044786e:
        mov ecx,dword ptr [edi+10Ch]
    L_00447874:
        inc eax
    L_00447875:
        add ebx,10h
    L_00447878:
        cmp eax,ecx
    L_0044787a:
        mov dword ptr [esp+0Ch],eax
    L_0044787e:
        jl short L_00447840
    L_00447880:
        pop esi
    L_00447881:
        pop ebx
    L_00447882:
        mov eax,dword ptr [edi+120h]
    L_00447888:
        cmp eax,ebp
    L_0044788a:
        je short L_0044789b
    L_0044788c:
        push eax
    L_0044788d:
        call asm_free_00452422
    L_00447892:
        add esp,4
    L_00447895:
        mov dword ptr [edi+120h],ebp
    L_0044789b:
        mov eax,dword ptr [edi+118h]
    L_004478a1:
        cmp eax,ebp
    L_004478a3:
        je short L_004478b4
    L_004478a5:
        push eax
    L_004478a6:
        call asm_free_00452422
    L_004478ab:
        add esp,4
    L_004478ae:
        mov dword ptr [edi+118h],ebp
    L_004478b4:
        mov eax,dword ptr [edi+11Ch]
    L_004478ba:
        cmp eax,ebp
    L_004478bc:
        je short L_004478cd
    L_004478be:
        push eax
    L_004478bf:
        call asm_free_00452422
    L_004478c4:
        add esp,4
    L_004478c7:
        mov dword ptr [edi+11Ch],ebp
    L_004478cd:
        mov eax,dword ptr [edi+12Ch]
    L_004478d3:
        cmp eax,ebp
    L_004478d5:
        je short L_004478e6
    L_004478d7:
        push eax
    L_004478d8:
        call asm_free_00452422
    L_004478dd:
        add esp,4
    L_004478e0:
        mov dword ptr [edi+12Ch],ebp
    L_004478e6:
        mov eax,dword ptr [edi+108h]
    L_004478ec:
        cmp eax,ebp
    L_004478ee:
        je short L_004478ff
    L_004478f0:
        push eax
    L_004478f1:
        call asm_free_00452422
    L_004478f6:
        add esp,4
    L_004478f9:
        mov dword ptr [edi+108h],ebp
    L_004478ff:
        pop ebp
    L_00447900:
        pop ecx
    L_00447901:
        ret
    }
}

// 0x00447940..0x004479CE: ?AnimationManager_CopyPositionRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CopyPositionRecord_00447940() {
    __asm {
    L_00447940:
        imul eax,44h
    L_00447943:
        push esi
    L_00447944:
        push edi
    L_00447945:
        mov edi,dword ptr [edx+118h]
    L_0044794b:
        add edi,eax
    L_0044794d:
        mov ecx,11h
    L_00447952:
        mov esi,ebx
    L_00447954:
        rep movsd
    L_00447956:
        mov ecx,dword ptr [edx+118h]
    L_0044795c:
        add ecx,eax
    L_0044795e:
        pop edi
    L_0044795f:
        pop esi
    L_00447960:
        fld dword ptr [ecx+8]
    L_00447963:
        fdiv dword ptr [ecx+1Ch]
    L_00447966:
        fstp dword ptr [ecx+20h]
    L_00447969:
        mov ecx,dword ptr [edx+118h]
    L_0044796f:
        fld dword ptr [ecx+eax+10h]
    L_00447973:
        fdiv dword ptr [ecx+eax+1Ch]
    L_00447977:
        add ecx,eax
    L_00447979:
        fstp dword ptr [ecx+28h]
    L_0044797c:
        mov ecx,dword ptr [edx+118h]
    L_00447982:
        fld dword ptr [ecx+eax+0Ch]
    L_00447986:
        fdiv dword ptr [ecx+eax+18h]
    L_0044798a:
        add ecx,eax
    L_0044798c:
        fstp dword ptr [ecx+24h]
    L_0044798f:
        mov ecx,dword ptr [edx+118h]
    L_00447995:
        fld dword ptr [ecx+eax+14h]
    L_00447999:
        fdiv dword ptr [ecx+eax+18h]
    L_0044799d:
        add ecx,eax
    L_0044799f:
        fstp dword ptr [ecx+2Ch]
    L_004479a2:
        mov ecx,dword ptr [edx+118h]
    L_004479a8:
        fld dword ptr [ecx+eax+10h]
    L_004479ac:
        fsub dword ptr [ecx+eax+8]
    L_004479b0:
        add ecx,eax
    L_004479b2:
        fdiv dword ptr [ebx+38h]
    L_004479b5:
        fstp dword ptr [ecx+34h]
    L_004479b8:
        mov edx,dword ptr [edx+118h]
    L_004479be:
        fld dword ptr [eax+edx+14h]
    L_004479c2:
        fsub dword ptr [eax+edx+0Ch]
    L_004479c6:
        add eax,edx
    L_004479c8:
        fdiv dword ptr [ebx+3Ch]
    L_004479cb:
        fstp dword ptr [eax+30h]
    L_004479ce:
        ret
    }
}

// 0x00447F70..0x00447FC6: ?AnimationManager_ClearIndexedResources@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearIndexedResources_00447f70() {
    __asm {
    L_00447f70:
        mov eax,dword ptr [edi+esi*4+3AD4E0h]
    L_00447f77:
        push ebx
    L_00447f78:
        xor ebx,ebx
    L_00447f7a:
        cmp eax,ebx
    L_00447f7c:
        je short L_00447f8b
    L_00447f7e:
        mov ecx,dword ptr [eax]
    L_00447f80:
        push eax
    L_00447f81:
        call dword ptr [ecx+8]
    L_00447f84:
        mov dword ptr [edi+esi*4+3AD4E0h],ebx
    L_00447f8b:
        mov eax,dword ptr [edi+esi*4+3AD560h]
    L_00447f92:
        cmp eax,ebx
    L_00447f94:
        je short L_00447fa3
    L_00447f96:
        mov edx,dword ptr [eax]
    L_00447f98:
        push eax
    L_00447f99:
        call dword ptr [edx+8]
    L_00447f9c:
        mov dword ptr [edi+esi*4+3AD560h],ebx
    L_00447fa3:
        mov eax,dword ptr [edi+esi*4+3AD5E0h]
    L_00447faa:
        cmp eax,ebx
    L_00447fac:
        je short L_00447fbe
    L_00447fae:
        push eax
    L_00447faf:
        call asm_free_00452422
    L_00447fb4:
        add esp,4
    L_00447fb7:
        mov dword ptr [edi+esi*4+3AD5E0h],ebx
    L_00447fbe:
        mov dword ptr [edi+esi*4+3AD5E0h],ebx
    L_00447fc5:
        pop ebx
    L_00447fc6:
        ret
    }
}

// 0x00448860..0x004488F4: ?AnimationManager_UpdatePrimary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_UpdatePrimary_00448860() {
    __asm {
    L_00448860:
        sub esp,50h
    L_00448863:
        push ebp
    L_00448864:
        push edi
    L_00448865:
        mov edi,eax
    L_00448867:
        xor ebp,ebp
    L_00448869:
        xor eax,eax
    L_0044886b:
        lea ecx,[edi+72DAE4h]
    L_00448871:
        mov dword ptr [esp+eax*4+8],ecx
    L_00448875:
        mov dword ptr [ecx+1Ch],ebp
    L_00448878:
        inc eax
    L_00448879:
        add ecx,3ACh
    L_0044887f:
        cmp eax,13h
    L_00448882:
        jl short L_00448871
    L_00448884:
        mov eax,dword ptr [edi+72DAD4h]
    L_0044888a:
        cmp eax,ebp
    L_0044888c:
        je short L_004488ea
    L_0044888e:
        push ebx
    L_0044888f:
        push esi
    L_00448890:
        mov esi,dword ptr [eax]
    L_00448892:
        mov ebx,dword ptr [eax+4]
    L_00448895:
        test dword ptr [esi+35Ch],4000000h
    L_0044889f:
        je short L_004488a8
    L_004488a1:
        call asm_FUN_00448bb0_00448bb0
    L_004488a6:
        jmp short L_004488db
    L_004488a8:
        mov eax,dword ptr [esi+398h]
    L_004488ae:
        cmp eax,ebp
    L_004488b0:
        je short L_004488b6
    L_004488b2:
        mov ecx,esi
    L_004488b4:
        call eax
    L_004488b6:
        push esi
    L_004488b7:
        call asm_FUN_0043ee30_0043ee30
    L_004488bc:
        test eax,eax
    L_004488be:
        je short L_004488c7
    L_004488c0:
        call asm_FUN_00448bb0_00448bb0
    L_004488c5:
        jmp short L_004488db
    L_004488c7:
        mov eax,dword ptr [esi+20h]
    L_004488ca:
        mov ecx,dword ptr [esp+eax*4+10h]
    L_004488ce:
        mov dword ptr [ecx+1Ch],esi
    L_004488d1:
        mov edx,dword ptr [esi+20h]
    L_004488d4:
        mov dword ptr [esp+edx*4+10h],esi
    L_004488d8:
        mov dword ptr [esi+1Ch],ebp
    L_004488db:
        mov edx,dword ptr [edi+64h]
    L_004488de:
        inc edx
    L_004488df:
        cmp ebx,ebp
    L_004488e1:
        mov dword ptr [edi+64h],edx
    L_004488e4:
        mov eax,ebx
    L_004488e6:
        jne short L_00448890
    L_004488e8:
        pop esi
    L_004488e9:
        pop ebx
    L_004488ea:
        pop edi
    L_004488eb:
        mov eax,1
    L_004488f0:
        pop ebp
    L_004488f1:
        add esp,50h
    L_004488f4:
        ret
    }
}

// 0x00448900..0x0044897A: ?AnimationManager_UpdateSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_UpdateSecondary_00448900() {
    __asm {
    L_00448900:
        push ebp
    L_00448901:
        push edi
    L_00448902:
        mov edi,eax
    L_00448904:
        mov eax,dword ptr [edi+72DADCh]
    L_0044890a:
        xor ecx,ecx
    L_0044890c:
        cmp eax,ecx
    L_0044890e:
        mov dword ptr [edi+7320C4h],ecx
    L_00448914:
        lea ebp,[edi+7320A8h]
    L_0044891a:
        mov dword ptr [edi+64h],ecx
    L_0044891d:
        je short L_00448973
    L_0044891f:
        push ebx
    L_00448920:
        push esi
    L_00448921:
        mov esi,dword ptr [eax]
    L_00448923:
        mov ebx,dword ptr [eax+4]
    L_00448926:
        test dword ptr [esi+35Ch],4000000h
    L_00448930:
        je short L_00448939
    L_00448932:
        call asm_FUN_00448bb0_00448bb0
    L_00448937:
        jmp short L_00448964
    L_00448939:
        mov eax,dword ptr [esi+398h]
    L_0044893f:
        test eax,eax
    L_00448941:
        je short L_00448947
    L_00448943:
        mov ecx,esi
    L_00448945:
        call eax
    L_00448947:
        push esi
    L_00448948:
        call asm_FUN_0043ee30_0043ee30
    L_0044894d:
        test eax,eax
    L_0044894f:
        je short L_00448958
    L_00448951:
        call asm_FUN_00448bb0_00448bb0
    L_00448956:
        jmp short L_00448964
    L_00448958:
        mov dword ptr [ebp+1Ch],esi
    L_0044895b:
        mov ebp,esi
    L_0044895d:
        mov dword ptr [esi+1Ch],0
    L_00448964:
        mov edx,dword ptr [edi+64h]
    L_00448967:
        inc edx
    L_00448968:
        test ebx,ebx
    L_0044896a:
        mov dword ptr [edi+64h],edx
    L_0044896d:
        mov eax,ebx
    L_0044896f:
        jne short L_00448921
    L_00448971:
        pop esi
    L_00448972:
        pop ebx
    L_00448973:
        pop edi
    L_00448974:
        mov eax,1
    L_00448979:
        pop ebp
    L_0044897a:
        ret
    }
}

// 0x00448980..0x004489C2: ?AnimationManager_RenderBucket@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RenderBucket_00448980() {
    __asm {
    L_00448980:
        imul eax,3ACh
    L_00448986:
        push esi
    L_00448987:
        mov esi,dword ptr [eax+edi+72DB00h]
    L_0044898e:
        test esi,esi
    L_00448990:
        je short L_004489bc
    L_00448992:
        test dword ptr [esi+35Ch],4000000h
    L_0044899c:
        jne short L_004489b5
    L_0044899e:
        mov eax,dword ptr [esi+39Ch]
    L_004489a4:
        test eax,eax
    L_004489a6:
        je short L_004489ac
    L_004489a8:
        mov ecx,esi
    L_004489aa:
        call eax
    L_004489ac:
        mov eax,esi
    L_004489ae:
        mov ecx,edi
    L_004489b0:
        call asm_FUN_004451c0_004451c0
    L_004489b5:
        mov esi,dword ptr [esi+1Ch]
    L_004489b8:
        test esi,esi
    L_004489ba:
        jne short L_00448992
    L_004489bc:
        mov eax,1
    L_004489c1:
        pop esi
    L_004489c2:
        ret
    }
}

// 0x004489D0..0x00448A45: ?AnimationManager_RegisterPrimaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0() {
    __asm {
    L_004489d0:
        lea ecx,[ebx+4]
    L_004489d3:
        push esi
    L_004489d4:
        mov dword ptr [ecx],ebx
    L_004489d6:
        mov dword ptr [ecx+4],0
    L_004489dd:
        mov dword ptr [ecx+8],0
    L_004489e4:
        mov esi,dword ptr [edx+72DAD4h]
    L_004489ea:
        test esi,esi
    L_004489ec:
        jne short L_004489f6
    L_004489ee:
        mov dword ptr [edx+72DAD4h],ecx
    L_004489f4:
        jmp short L_00448a14
    L_004489f6:
        mov esi,dword ptr [edx+72DAD8h]
    L_004489fc:
        push edi
    L_004489fd:
        mov edi,dword ptr [esi+4]
    L_00448a00:
        test edi,edi
    L_00448a02:
        je short L_00448a0d
    L_00448a04:
        mov dword ptr [ecx+4],edi
    L_00448a07:
        mov edi,dword ptr [esi+4]
    L_00448a0a:
        mov dword ptr [edi+8],ecx
    L_00448a0d:
        mov dword ptr [esi+4],ecx
    L_00448a10:
        mov dword ptr [ecx+8],esi
    L_00448a13:
        pop edi
    L_00448a14:
        mov dword ptr [edx+72DAD8h],ecx
    L_00448a1a:
        mov esi,dword ptr [edx+732454h]
    L_00448a20:
        inc esi
    L_00448a21:
        mov ecx,esi
    L_00448a23:
        test ecx,ecx
    L_00448a25:
        mov dword ptr [edx+732454h],esi
    L_00448a2b:
        pop esi
    L_00448a2c:
        jne short L_00448a35
    L_00448a2e:
        inc ecx
    L_00448a2f:
        mov dword ptr [edx+732454h],ecx
    L_00448a35:
        mov ecx,dword ptr [edx+732454h]
    L_00448a3b:
        mov dword ptr [ebx],ecx
    L_00448a3d:
        mov edx,dword ptr [edx+732454h]
    L_00448a43:
        mov dword ptr [eax],edx
    L_00448a45:
        ret
    }
}

// 0x00448A50..0x00448ABF: ?AnimationManager_RegisterPrimaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50() {
    __asm {
    L_00448a50:
        lea ecx,[ebx+4]
    L_00448a53:
        push esi
    L_00448a54:
        mov dword ptr [ecx],ebx
    L_00448a56:
        mov dword ptr [ecx+4],0
    L_00448a5d:
        mov dword ptr [ecx+8],0
    L_00448a64:
        mov esi,dword ptr [edx+72DAD4h]
    L_00448a6a:
        test esi,esi
    L_00448a6c:
        jne short L_00448a76
    L_00448a6e:
        mov dword ptr [edx+72DAD8h],ecx
    L_00448a74:
        jmp short L_00448a8e
    L_00448a76:
        push edi
    L_00448a77:
        mov edi,dword ptr [ecx+4]
    L_00448a7a:
        test edi,edi
    L_00448a7c:
        je short L_00448a87
    L_00448a7e:
        mov dword ptr [esi+4],edi
    L_00448a81:
        mov edi,dword ptr [ecx+4]
    L_00448a84:
        mov dword ptr [edi+8],esi
    L_00448a87:
        mov dword ptr [ecx+4],esi
    L_00448a8a:
        mov dword ptr [esi+8],ecx
    L_00448a8d:
        pop edi
    L_00448a8e:
        mov dword ptr [edx+72DAD4h],ecx
    L_00448a94:
        mov esi,dword ptr [edx+732454h]
    L_00448a9a:
        inc esi
    L_00448a9b:
        mov ecx,esi
    L_00448a9d:
        test ecx,ecx
    L_00448a9f:
        mov dword ptr [edx+732454h],esi
    L_00448aa5:
        pop esi
    L_00448aa6:
        jne short L_00448aaf
    L_00448aa8:
        inc ecx
    L_00448aa9:
        mov dword ptr [edx+732454h],ecx
    L_00448aaf:
        mov ecx,dword ptr [edx+732454h]
    L_00448ab5:
        mov dword ptr [ebx],ecx
    L_00448ab7:
        mov edx,dword ptr [edx+732454h]
    L_00448abd:
        mov dword ptr [eax],edx
    L_00448abf:
        ret
    }
}

// 0x00448AC0..0x00448B35: ?AnimationManager_RegisterSecondaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterSecondaryBack_00448ac0() {
    __asm {
    L_00448ac0:
        lea ecx,[ebx+4]
    L_00448ac3:
        push esi
    L_00448ac4:
        mov dword ptr [ecx],ebx
    L_00448ac6:
        mov dword ptr [ecx+4],0
    L_00448acd:
        mov dword ptr [ecx+8],0
    L_00448ad4:
        mov esi,dword ptr [edx+72DADCh]
    L_00448ada:
        test esi,esi
    L_00448adc:
        jne short L_00448ae6
    L_00448ade:
        mov dword ptr [edx+72DADCh],ecx
    L_00448ae4:
        jmp short L_00448b04
    L_00448ae6:
        mov esi,dword ptr [edx+72DAE0h]
    L_00448aec:
        push edi
    L_00448aed:
        mov edi,dword ptr [esi+4]
    L_00448af0:
        test edi,edi
    L_00448af2:
        je short L_00448afd
    L_00448af4:
        mov dword ptr [ecx+4],edi
    L_00448af7:
        mov edi,dword ptr [esi+4]
    L_00448afa:
        mov dword ptr [edi+8],ecx
    L_00448afd:
        mov dword ptr [esi+4],ecx
    L_00448b00:
        mov dword ptr [ecx+8],esi
    L_00448b03:
        pop edi
    L_00448b04:
        mov dword ptr [edx+72DAE0h],ecx
    L_00448b0a:
        mov esi,dword ptr [edx+732454h]
    L_00448b10:
        inc esi
    L_00448b11:
        mov ecx,esi
    L_00448b13:
        test ecx,ecx
    L_00448b15:
        mov dword ptr [edx+732454h],esi
    L_00448b1b:
        pop esi
    L_00448b1c:
        jne short L_00448b25
    L_00448b1e:
        inc ecx
    L_00448b1f:
        mov dword ptr [edx+732454h],ecx
    L_00448b25:
        mov ecx,dword ptr [edx+732454h]
    L_00448b2b:
        mov dword ptr [ebx],ecx
    L_00448b2d:
        mov edx,dword ptr [edx+732454h]
    L_00448b33:
        mov dword ptr [eax],edx
    L_00448b35:
        ret
    }
}

// 0x00448B40..0x00448BAF: ?AnimationManager_RegisterSecondaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterSecondaryFront_00448b40() {
    __asm {
    L_00448b40:
        lea ecx,[ebx+4]
    L_00448b43:
        push esi
    L_00448b44:
        mov dword ptr [ecx],ebx
    L_00448b46:
        mov dword ptr [ecx+4],0
    L_00448b4d:
        mov dword ptr [ecx+8],0
    L_00448b54:
        mov esi,dword ptr [edx+72DADCh]
    L_00448b5a:
        test esi,esi
    L_00448b5c:
        jne short L_00448b66
    L_00448b5e:
        mov dword ptr [edx+72DAE0h],ecx
    L_00448b64:
        jmp short L_00448b7e
    L_00448b66:
        push edi
    L_00448b67:
        mov edi,dword ptr [ecx+4]
    L_00448b6a:
        test edi,edi
    L_00448b6c:
        je short L_00448b77
    L_00448b6e:
        mov dword ptr [esi+4],edi
    L_00448b71:
        mov edi,dword ptr [ecx+4]
    L_00448b74:
        mov dword ptr [edi+8],esi
    L_00448b77:
        mov dword ptr [ecx+4],esi
    L_00448b7a:
        mov dword ptr [esi+8],ecx
    L_00448b7d:
        pop edi
    L_00448b7e:
        mov dword ptr [edx+72DADCh],ecx
    L_00448b84:
        mov esi,dword ptr [edx+732454h]
    L_00448b8a:
        inc esi
    L_00448b8b:
        mov ecx,esi
    L_00448b8d:
        test ecx,ecx
    L_00448b8f:
        mov dword ptr [edx+732454h],esi
    L_00448b95:
        pop esi
    L_00448b96:
        jne short L_00448b9f
    L_00448b98:
        inc ecx
    L_00448b99:
        mov dword ptr [edx+732454h],ecx
    L_00448b9f:
        mov ecx,dword ptr [edx+732454h]
    L_00448ba5:
        mov dword ptr [ebx],ecx
    L_00448ba7:
        mov edx,dword ptr [edx+732454h]
    L_00448bad:
        mov dword ptr [eax],edx
    L_00448baf:
        ret
    }
}

// 0x00448BB0..0x00448CBB: FUN_00448bb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448bb0_00448bb0() {
    __asm {
    L_00448bb0:
        mov ecx,dword ptr [edi+72DAD8h]
    L_00448bb6:
        lea eax,[esi+4]
    L_00448bb9:
        cmp eax,ecx
    L_00448bbb:
        jne short L_00448bc6
    L_00448bbd:
        mov ecx,dword ptr [esi+0Ch]
    L_00448bc0:
        mov dword ptr [edi+72DAD8h],ecx
    L_00448bc6:
        cmp eax,dword ptr [edi+72DAD4h]
    L_00448bcc:
        jne short L_00448bd7
    L_00448bce:
        mov edx,dword ptr [esi+8]
    L_00448bd1:
        mov dword ptr [edi+72DAD4h],edx
    L_00448bd7:
        cmp eax,dword ptr [edi+72DAE0h]
    L_00448bdd:
        jne short L_00448be8
    L_00448bdf:
        mov ecx,dword ptr [esi+0Ch]
    L_00448be2:
        mov dword ptr [edi+72DAE0h],ecx
    L_00448be8:
        cmp eax,dword ptr [edi+72DADCh]
    L_00448bee:
        jne short L_00448bf9
    L_00448bf0:
        mov edx,dword ptr [esi+8]
    L_00448bf3:
        mov dword ptr [edi+72DADCh],edx
    L_00448bf9:
        mov ecx,dword ptr [eax+4]
    L_00448bfc:
        push ebx
    L_00448bfd:
        xor ebx,ebx
    L_00448bff:
        cmp ecx,ebx
    L_00448c01:
        je short L_00448c09
    L_00448c03:
        mov edx,dword ptr [eax+8]
    L_00448c06:
        mov dword ptr [ecx+8],edx
    L_00448c09:
        mov ecx,dword ptr [eax+8]
    L_00448c0c:
        cmp ecx,ebx
    L_00448c0e:
        je short L_00448c16
    L_00448c10:
        mov edx,dword ptr [eax+4]
    L_00448c13:
        mov dword ptr [ecx+4],edx
    L_00448c16:
        mov dword ptr [eax+4],ebx
    L_00448c19:
        mov dword ptr [eax+8],ebx
    L_00448c1c:
        mov eax,dword ptr [esi+14h]
    L_00448c1f:
        cmp eax,ebx
    L_00448c21:
        je short L_00448c29
    L_00448c23:
        mov ecx,dword ptr [esi+18h]
    L_00448c26:
        mov dword ptr [eax+8],ecx
    L_00448c29:
        mov eax,dword ptr [esi+18h]
    L_00448c2c:
        cmp eax,ebx
    L_00448c2e:
        je short L_00448c36
    L_00448c30:
        mov edx,dword ptr [esi+14h]
    L_00448c33:
        mov dword ptr [eax+4],edx
    L_00448c36:
        lea eax,[edi+68h]
    L_00448c39:
        cmp esi,eax
    L_00448c3b:
        mov dword ptr [esi+14h],ebx
    L_00448c3e:
        mov dword ptr [esi+18h],ebx
    L_00448c41:
        jb short L_00448c92
    L_00448c43:
        lea ecx,[edi+3AC068h]
    L_00448c49:
        cmp esi,ecx
    L_00448c4b:
        jae short L_00448c92
    L_00448c4d:
        mov ecx,esi
    L_00448c4f:
        sub ecx,edi
    L_00448c51:
        sub ecx,68h
    L_00448c54:
        mov eax,8B70344Bh
    L_00448c59:
        imul ecx
    L_00448c5b:
        add edx,ecx
    L_00448c5d:
        sar edx,9
    L_00448c60:
        mov eax,edx
    L_00448c62:
        shr eax,1Fh
    L_00448c65:
        add eax,edx
    L_00448c67:
        mov byte ptr [eax+edi+3AC068h],bl
    L_00448c6e:
        mov eax,dword ptr [esi+358h]
    L_00448c74:
        cmp eax,ebx
    L_00448c76:
        je short L_00448c81
    L_00448c78:
        push eax
    L_00448c79:
        call asm_free_00452422
    L_00448c7e:
        add esp,4
    L_00448c81:
        mov edx,esi
    L_00448c83:
        mov dword ptr [esi+358h],ebx
    L_00448c89:
        call asm_InitializeEntity_00401de0
    L_00448c8e:
        xor eax,eax
    L_00448c90:
        pop ebx
    L_00448c91:
        ret
    L_00448c92:
        cmp esi,ebx
    L_00448c94:
        je short L_00448cb8
    L_00448c96:
        mov eax,dword ptr [esi+358h]
    L_00448c9c:
        cmp eax,ebx
    L_00448c9e:
        je short L_00448ca9
    L_00448ca0:
        push eax
    L_00448ca1:
        call asm_free_00452422
    L_00448ca6:
        add esp,4
    L_00448ca9:
        push esi
    L_00448caa:
        mov dword ptr [esi+358h],ebx
    L_00448cb0:
        call asm_free_004524a1
    L_00448cb5:
        add esp,4
    L_00448cb8:
        xor eax,eax
    L_00448cba:
        pop ebx
    L_00448cbb:
        ret
    }
}

// 0x00448D00..0x00448D48: ?AnimationManager_CreatePrimaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePrimaryBack_00448d00() {
    __asm {
    L_00448d00:
        push ebx
    L_00448d01:
        push esi
    L_00448d02:
        mov esi,dword ptr [data_00491c10]
    L_00448d08:
        call asm_FUN_00449950_00449950
    L_00448d0d:
        mov ecx,dword ptr [esp+10h]
    L_00448d11:
        mov ebx,eax
    L_00448d13:
        mov esi,dword ptr [ebx+35Ch]
    L_00448d19:
        mov eax,dword ptr [esp+14h]
    L_00448d1d:
        push ecx
    L_00448d1e:
        mov ecx,dword ptr [esp+10h]
    L_00448d22:
        or esi,40000000h
    L_00448d28:
        push ebx
    L_00448d29:
        mov dword ptr [ebx+20h],eax
    L_00448d2c:
        mov dword ptr [ebx+35Ch],esi
    L_00448d32:
        call asm_FUN_00449870_00449870
    L_00448d37:
        mov edx,dword ptr [data_00491c10]
    L_00448d3d:
        mov eax,edi
    L_00448d3f:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448d44:
        pop esi
    L_00448d45:
        pop ebx
    L_00448d46:
        ret 0Ch
    }
}

// 0x00448D50..0x00448DAE: ?AnimationManager_CreatePositionedPrimary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePositionedPrimary_00448d50() {
    __asm {
    L_00448d50:
        push ebx
    L_00448d51:
        push ebp
    L_00448d52:
        mov ebp,dword ptr [esp+10h]
    L_00448d56:
        push esi
    L_00448d57:
        mov esi,dword ptr [data_00491c10]
    L_00448d5d:
        call asm_FUN_00449950_00449950
    L_00448d62:
        mov ebx,dword ptr [esp+18h]
    L_00448d66:
        mov esi,eax
    L_00448d68:
        or dword ptr [esi+35Ch],40000000h
    L_00448d72:
        mov dword ptr [esi+20h],0
    L_00448d79:
        mov ecx,dword ptr [edi]
    L_00448d7b:
        lea eax,[esi+340h]
    L_00448d81:
        mov dword ptr [eax],ecx
    L_00448d83:
        mov edx,dword ptr [edi+4]
    L_00448d86:
        mov dword ptr [eax+4],edx
    L_00448d89:
        mov ecx,dword ptr [edi+8]
    L_00448d8c:
        mov dword ptr [eax+8],ecx
    L_00448d8f:
        mov ecx,dword ptr [esp+10h]
    L_00448d93:
        mov eax,esi
    L_00448d95:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448d9a:
        mov edx,dword ptr [data_00491c10]
    L_00448da0:
        mov ebx,esi
    L_00448da2:
        mov eax,ebp
    L_00448da4:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448da9:
        pop esi
    L_00448daa:
        pop ebp
    L_00448dab:
        pop ebx
    L_00448dac:
        ret 0Ch
    }
}

// 0x00448DB0..0x00448E25: ?PlayerAnimation_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PlayerAnimation_Create_00448db0() {
    __asm {
    L_00448db0:
        push ebx
    L_00448db1:
        push ebp
    L_00448db2:
        mov ebp,dword ptr [esp+10h]
    L_00448db6:
        push esi
    L_00448db7:
        mov esi,dword ptr [data_00491c10]
    L_00448dbd:
        call asm_FUN_00449950_00449950
    L_00448dc2:
        mov esi,eax
    L_00448dc4:
        mov eax,dword ptr [esi+35Ch]
    L_00448dca:
        mov ebx,dword ptr [esp+18h]
    L_00448dce:
        mov ecx,dword ptr [esp+10h]
    L_00448dd2:
        mov dword ptr [esi+20h],0
    L_00448dd9:
        or eax,40000000h
    L_00448dde:
        mov dword ptr [esi+35Ch],eax
    L_00448de4:
        fld dword ptr [edi]
    L_00448de6:
        fadd dword ptr [data_00470b4c]
    L_00448dec:
        fstp dword ptr [esi+340h]
    L_00448df2:
        fld dword ptr [edi+4]
    L_00448df5:
        fadd dword ptr [data_00470b48]
    L_00448dfb:
        fstp dword ptr [esi+344h]
    L_00448e01:
        mov eax,dword ptr [edi+8]
    L_00448e04:
        mov dword ptr [esi+348h],eax
    L_00448e0a:
        mov eax,esi
    L_00448e0c:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448e11:
        mov edx,dword ptr [data_00491c10]
    L_00448e17:
        mov ebx,esi
    L_00448e19:
        mov eax,ebp
    L_00448e1b:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448e20:
        pop esi
    L_00448e21:
        pop ebp
    L_00448e22:
        pop ebx
    L_00448e23:
        ret 0Ch
    }
}

// 0x00448E30..0x00448E78: ?AnimationManager_CreatePrimaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePrimaryFront_00448e30() {
    __asm {
    L_00448e30:
        push ebx
    L_00448e31:
        push esi
    L_00448e32:
        mov esi,dword ptr [data_00491c10]
    L_00448e38:
        call asm_FUN_00449950_00449950
    L_00448e3d:
        mov ecx,dword ptr [esp+10h]
    L_00448e41:
        mov ebx,eax
    L_00448e43:
        mov esi,dword ptr [ebx+35Ch]
    L_00448e49:
        mov eax,dword ptr [esp+14h]
    L_00448e4d:
        push ecx
    L_00448e4e:
        mov ecx,dword ptr [esp+10h]
    L_00448e52:
        or esi,40000000h
    L_00448e58:
        push ebx
    L_00448e59:
        mov dword ptr [ebx+20h],eax
    L_00448e5c:
        mov dword ptr [ebx+35Ch],esi
    L_00448e62:
        call asm_FUN_00449870_00449870
    L_00448e67:
        mov edx,dword ptr [data_00491c10]
    L_00448e6d:
        mov eax,edi
    L_00448e6f:
        call asm_AnimationManager_RegisterPrimaryFront_00448a50
    L_00448e74:
        pop esi
    L_00448e75:
        pop ebx
    L_00448e76:
        ret 0Ch
    }
}

// 0x00448F60..0x00448FA8: ?AnimationManager_CreateSecondaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreateSecondaryBack_00448f60() {
    __asm {
    L_00448f60:
        push ebx
    L_00448f61:
        push esi
    L_00448f62:
        mov esi,dword ptr [data_00491c10]
    L_00448f68:
        call asm_FUN_00449950_00449950
    L_00448f6d:
        mov ecx,dword ptr [esp+10h]
    L_00448f71:
        mov ebx,eax
    L_00448f73:
        mov esi,dword ptr [ebx+35Ch]
    L_00448f79:
        mov eax,dword ptr [esp+14h]
    L_00448f7d:
        push ecx
    L_00448f7e:
        mov ecx,dword ptr [esp+10h]
    L_00448f82:
        or esi,40000000h
    L_00448f88:
        push ebx
    L_00448f89:
        mov dword ptr [ebx+20h],eax
    L_00448f8c:
        mov dword ptr [ebx+35Ch],esi
    L_00448f92:
        call asm_FUN_00449870_00449870
    L_00448f97:
        mov edx,dword ptr [data_00491c10]
    L_00448f9d:
        mov eax,edi
    L_00448f9f:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00448fa4:
        pop esi
    L_00448fa5:
        pop ebx
    L_00448fa6:
        ret 0Ch
    }
}

// 0x00449090..0x004490D8: ?AnimationManager_CreateSecondaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreateSecondaryFront_00449090() {
    __asm {
    L_00449090:
        push ebx
    L_00449091:
        push esi
    L_00449092:
        mov esi,dword ptr [data_00491c10]
    L_00449098:
        call asm_FUN_00449950_00449950
    L_0044909d:
        mov ecx,dword ptr [esp+10h]
    L_004490a1:
        mov ebx,eax
    L_004490a3:
        mov esi,dword ptr [ebx+35Ch]
    L_004490a9:
        mov eax,dword ptr [esp+14h]
    L_004490ad:
        push ecx
    L_004490ae:
        mov ecx,dword ptr [esp+10h]
    L_004490b2:
        or esi,40000000h
    L_004490b8:
        push ebx
    L_004490b9:
        mov dword ptr [ebx+20h],eax
    L_004490bc:
        mov dword ptr [ebx+35Ch],esi
    L_004490c2:
        call asm_FUN_00449870_00449870
    L_004490c7:
        mov edx,dword ptr [data_00491c10]
    L_004490cd:
        mov eax,edi
    L_004490cf:
        call asm_AnimationManager_RegisterSecondaryFront_00448b40
    L_004490d4:
        pop esi
    L_004490d5:
        pop ebx
    L_004490d6:
        ret 0Ch
    }
}

// 0x004491C0..0x00449208: ?AnimationManager_Find@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_Find_004491c0() {
    __asm {
    L_004491c0:
        mov ecx,dword ptr [esp+4]
    L_004491c4:
        test ecx,ecx
    L_004491c6:
        jne short L_004491cd
    L_004491c8:
        xor eax,eax
    L_004491ca:
        ret 4
    L_004491cd:
        mov eax,dword ptr [edx+72DAD4h]
    L_004491d3:
        test eax,eax
    L_004491d5:
        push esi
    L_004491d6:
        je short L_004491e5
    L_004491d8:
        mov esi,dword ptr [eax]
    L_004491da:
        cmp dword ptr [esi],ecx
    L_004491dc:
        je short L_00449203
    L_004491de:
        mov eax,dword ptr [eax+4]
    L_004491e1:
        test eax,eax
    L_004491e3:
        jne short L_004491d8
    L_004491e5:
        mov eax,dword ptr [edx+72DADCh]
    L_004491eb:
        test eax,eax
    L_004491ed:
        je short L_004491fd
    L_004491ef:
        nop
    L_004491f0:
        mov edx,dword ptr [eax]
    L_004491f2:
        cmp dword ptr [edx],ecx
    L_004491f4:
        je short L_00449203
    L_004491f6:
        mov eax,dword ptr [eax+4]
    L_004491f9:
        test eax,eax
    L_004491fb:
        jne short L_004491f0
    L_004491fd:
        xor eax,eax
    L_004491ff:
        pop esi
    L_00449200:
        ret 4
    L_00449203:
        mov eax,dword ptr [eax]
    L_00449205:
        pop esi
    L_00449206:
        ret 4
    }
}

// 0x00449210..0x00449245: ?AnimationManager_SetStopFrame@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrame_00449210() {
    __asm {
    L_00449210:
        mov eax,dword ptr [esp+4]
    L_00449214:
        push eax
    L_00449215:
        call asm_AnimationManager_Find_004491c0
    L_0044921a:
        test eax,eax
    L_0044921c:
        je short L_00449243
    L_0044921e:
        mov ecx,dword ptr [eax+18h]
    L_00449221:
        test ecx,ecx
    L_00449223:
        mov word ptr [eax+304h],si
    L_0044922a:
        jne short L_00449243
    L_0044922c:
        mov eax,dword ptr [eax+14h]
    L_0044922f:
        test eax,eax
    L_00449231:
        je short L_00449243
    L_00449233:
        mov ecx,dword ptr [eax]
    L_00449235:
        mov word ptr [ecx+304h],si
    L_0044923c:
        mov eax,dword ptr [eax+4]
    L_0044923f:
        test eax,eax
    L_00449241:
        jne short L_00449233
    L_00449243:
        ret 4
    }
}

// 0x00449250..0x0044929B: ?AnimationManager_SetStopFrameAndRun@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrameAndRun_00449250() {
    __asm {
    L_00449250:
        mov eax,dword ptr [esp+4]
    L_00449254:
        push esi
    L_00449255:
        push eax
    L_00449256:
        call asm_AnimationManager_Find_004491c0
    L_0044925b:
        mov esi,eax
    L_0044925d:
        test esi,esi
    L_0044925f:
        je short L_00449298
    L_00449261:
        push esi
    L_00449262:
        mov word ptr [esi+304h],di
    L_00449269:
        call asm_FUN_0043ee30_0043ee30
    L_0044926e:
        mov eax,dword ptr [esi+18h]
    L_00449271:
        test eax,eax
    L_00449273:
        jne short L_00449298
    L_00449275:
        mov esi,dword ptr [esi+14h]
    L_00449278:
        test esi,esi
    L_0044927a:
        je short L_00449298
    L_0044927c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00449280:
        mov ecx,dword ptr [esi]
    L_00449282:
        mov word ptr [ecx+304h],di
    L_00449289:
        mov edx,dword ptr [esi]
    L_0044928b:
        push edx
    L_0044928c:
        call asm_FUN_0043ee30_0043ee30
    L_00449291:
        mov esi,dword ptr [esi+4]
    L_00449294:
        test esi,esi
    L_00449296:
        jne short L_00449280
    L_00449298:
        pop esi
    L_00449299:
        ret 4
    }
}

// 0x004492A0..0x004492E1: ?AnimationManager_SetFlag@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetFlag_004492a0() {
    __asm {
    L_004492a0:
        mov eax,dword ptr [esp+4]
    L_004492a4:
        push eax
    L_004492a5:
        call asm_AnimationManager_Find_004491c0
    L_004492aa:
        test eax,eax
    L_004492ac:
        je short L_004492df
    L_004492ae:
        mov ecx,dword ptr [eax+35Ch]
    L_004492b4:
        mov edx,4000000h
    L_004492b9:
        or ecx,edx
    L_004492bb:
        mov dword ptr [eax+35Ch],ecx
    L_004492c1:
        mov ecx,dword ptr [eax+18h]
    L_004492c4:
        test ecx,ecx
    L_004492c6:
        jne short L_004492df
    L_004492c8:
        mov eax,dword ptr [eax+14h]
    L_004492cb:
        test eax,eax
    L_004492cd:
        je short L_004492df
    L_004492cf:
        nop
    L_004492d0:
        mov ecx,dword ptr [eax]
    L_004492d2:
        or dword ptr [ecx+35Ch],edx
    L_004492d8:
        mov eax,dword ptr [eax+4]
    L_004492db:
        test eax,eax
    L_004492dd:
        jne short L_004492d0
    L_004492df:
        ret 4
    }
}

// 0x004492F0..0x00449349: ?AnimationManager_SetPosition@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetPosition_004492f0() {
    __asm {
    L_004492f0:
        mov eax,dword ptr [esp+4]
    L_004492f4:
        push eax
    L_004492f5:
        call asm_AnimationManager_Find_004491c0
    L_004492fa:
        test eax,eax
    L_004492fc:
        je short L_00449347
    L_004492fe:
        push edi
    L_004492ff:
        mov edx,esi
    L_00449301:
        mov edi,dword ptr [edx]
    L_00449303:
        lea ecx,[eax+340h]
    L_00449309:
        mov dword ptr [ecx],edi
    L_0044930b:
        mov edi,dword ptr [edx+4]
    L_0044930e:
        mov dword ptr [ecx+4],edi
    L_00449311:
        mov edx,dword ptr [edx+8]
    L_00449314:
        mov dword ptr [ecx+8],edx
    L_00449317:
        mov ecx,dword ptr [eax+18h]
    L_0044931a:
        test ecx,ecx
    L_0044931c:
        jne short L_00449346
    L_0044931e:
        mov eax,dword ptr [eax+14h]
    L_00449321:
        test eax,eax
    L_00449323:
        je short L_00449346
    L_00449325:
        mov ecx,dword ptr [eax]
    L_00449327:
        add ecx,340h
    L_0044932d:
        mov edx,esi
    L_0044932f:
        mov edi,dword ptr [edx]
    L_00449331:
        mov dword ptr [ecx],edi
    L_00449333:
        mov edi,dword ptr [edx+4]
    L_00449336:
        mov dword ptr [ecx+4],edi
    L_00449339:
        mov edx,dword ptr [edx+8]
    L_0044933c:
        mov dword ptr [ecx+8],edx
    L_0044933f:
        mov eax,dword ptr [eax+4]
    L_00449342:
        test eax,eax
    L_00449344:
        jne short L_00449325
    L_00449346:
        pop edi
    L_00449347:
        ret 4
    }
}

// 0x00449350..0x004493BE: ?AnimationManager_SetTranslatedPosition@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetTranslatedPosition_00449350() {
    __asm {
    L_00449350:
        mov eax,dword ptr [esp+4]
    L_00449354:
        push eax
    L_00449355:
        call asm_AnimationManager_Find_004491c0
    L_0044935a:
        test eax,eax
    L_0044935c:
        je short L_004493bc
    L_0044935e:
        fld dword ptr [esi]
    L_00449360:
        fadd dword ptr [data_00470b4c]
    L_00449366:
        fstp dword ptr [eax+340h]
    L_0044936c:
        fld dword ptr [esi+4]
    L_0044936f:
        fadd dword ptr [data_00470b48]
    L_00449375:
        fstp dword ptr [eax+344h]
    L_0044937b:
        mov ecx,dword ptr [esi+8]
    L_0044937e:
        mov dword ptr [eax+348h],ecx
    L_00449384:
        mov ecx,dword ptr [eax+18h]
    L_00449387:
        test ecx,ecx
    L_00449389:
        jne short L_004493bc
    L_0044938b:
        mov ecx,dword ptr [eax+14h]
    L_0044938e:
        test ecx,ecx
    L_00449390:
        je short L_004493bc
    L_00449392:
        fld dword ptr [esi]
    L_00449394:
        mov eax,dword ptr [ecx]
    L_00449396:
        fadd dword ptr [data_00470b4c]
    L_0044939c:
        add eax,340h
    L_004493a1:
        fstp dword ptr [eax]
    L_004493a3:
        fld dword ptr [esi+4]
    L_004493a6:
        fadd dword ptr [data_00470b48]
    L_004493ac:
        fstp dword ptr [eax+4]
    L_004493af:
        mov edx,dword ptr [esi+8]
    L_004493b2:
        mov dword ptr [eax+8],edx
    L_004493b5:
        mov ecx,dword ptr [ecx+4]
    L_004493b8:
        test ecx,ecx
    L_004493ba:
        jne short L_00449392
    L_004493bc:
        ret 4
    }
}

// 0x004493E0..0x00449417: ?AnimationManager_MarkResourceForRemoval@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkResourceForRemoval_004493e0() {
    __asm {
    L_004493e0:
        push esi
    L_004493e1:
        mov esi,eax
    L_004493e3:
        mov eax,dword ptr [esi+72DAD4h]
    L_004493e9:
        test eax,eax
    L_004493eb:
        push edi
    L_004493ec:
        mov edi,4000000h
    L_004493f1:
        je short L_0044940c
    L_004493f3:
        mov ecx,dword ptr [eax+4]
    L_004493f6:
        mov eax,dword ptr [eax]
    L_004493f8:
        cmp dword ptr [eax+308h],edx
    L_004493fe:
        jne short L_00449406
    L_00449400:
        or dword ptr [eax+35Ch],edi
    L_00449406:
        test ecx,ecx
    L_00449408:
        mov eax,ecx
    L_0044940a:
        jne short L_004493f3
    L_0044940c:
        mov eax,dword ptr [esi+72DADCh]
    L_00449412:
        test eax,eax
    L_00449414:
        TH10_REL8(0x74, 0x00449414, VA_asm_target_00449439)
    L_00449416:
        TH10_REL8(0xeb, 0x00449416, VA_asm_AnimationManager_MarkResourceForRemoval_part_00449420)
    }
}

// 0x00449420..0x0044943B: ?AnimationManager_MarkResourceForRemoval@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkResourceForRemoval_part_00449420() {
    __asm {
    L_00449420:
        mov ecx,dword ptr [eax+4]
    L_00449423:
        mov eax,dword ptr [eax]
    L_00449425:
        cmp dword ptr [eax+308h],edx
    L_0044942b:
        jne short L_00449433
    L_0044942d:
        or dword ptr [eax+35Ch],edi
    L_00449433:
        test ecx,ecx
    L_00449435:
        mov eax,ecx
    L_00449437:
        jne short L_00449420
    L_00449439:
        pop edi
    L_0044943a:
        pop esi
    L_0044943b:
        ret
    }
}

// 0x00449450..0x00449464: ?AnimationManager_ValidateHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ValidateHandle_00449450() {
    __asm {
    L_00449450:
        mov eax,dword ptr [esi]
    L_00449452:
        mov edx,dword ptr [data_00491c10]
    L_00449458:
        push eax
    L_00449459:
        call asm_AnimationManager_Find_004491c0
    L_0044945e:
        test eax,eax
    L_00449460:
        jne short L_00449464
    L_00449462:
        mov dword ptr [esi],eax
    L_00449464:
        ret
    }
}

// 0x00449470..0x00449498: AnimationManager_SetStopFrameFromHandleRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrameFromHandleRetail_00449470() {
    __asm {
    L_00449470:
        mov eax,dword ptr [eax]
    L_00449472:
        mov edx,dword ptr [data_00491c10]
    L_00449478:
        push eax
    L_00449479:
        call asm_AnimationManager_Find_004491c0
    L_0044947e:
        test eax,eax
    L_00449480:
        TH10_REL8(0x74, 0x00449480, VA_asm_target_004494b0)
    L_00449482:
        mov ecx,dword ptr [eax+18h]
    L_00449485:
        test ecx,ecx
    L_00449487:
        mov word ptr [eax+304h],si
    L_0044948e:
        TH10_REL8(0x75, 0x0044948e, VA_asm_target_004494b0)
    L_00449490:
        mov eax,dword ptr [eax+14h]
    L_00449493:
        test eax,eax
    L_00449495:
        TH10_REL8(0x74, 0x00449495, VA_asm_target_004494b0)
    L_00449497:
        TH10_REL8(0xeb, 0x00449497, VA_asm_AnimationManager_SetStopFrameFromHandleRetail_part_004494a0)
    }
}

// 0x004494A0..0x004494B0: AnimationManager_SetStopFrameFromHandleRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetStopFrameFromHandleRetail_part_004494a0() {
    __asm {
    L_004494a0:
        mov ecx,dword ptr [eax]
    L_004494a2:
        mov word ptr [ecx+304h],si
    L_004494a9:
        mov eax,dword ptr [eax+4]
    L_004494ac:
        test eax,eax
    L_004494ae:
        jne short L_004494a0
    L_004494b0:
        ret
    }
}

// 0x00449590..0x004495D2: ?AnimationManager_SetFlagBit1@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetFlagBit1_00449590() {
    __asm {
    L_00449590:
        mov ecx,dword ptr [eax]
    L_00449592:
        mov edx,dword ptr [data_00491c10]
    L_00449598:
        push ecx
    L_00449599:
        call asm_AnimationManager_Find_004491c0
    L_0044959e:
        test eax,eax
    L_004495a0:
        je short L_004495d2
    L_004495a2:
        mov ecx,dword ptr [eax+35Ch]
    L_004495a8:
        mov edx,2
    L_004495ad:
        or ecx,edx
    L_004495af:
        mov dword ptr [eax+35Ch],ecx
    L_004495b5:
        mov ecx,dword ptr [eax+18h]
    L_004495b8:
        test ecx,ecx
    L_004495ba:
        jne short L_004495d2
    L_004495bc:
        mov eax,dword ptr [eax+14h]
    L_004495bf:
        test eax,eax
    L_004495c1:
        je short L_004495d2
    L_004495c3:
        mov ecx,dword ptr [eax]
    L_004495c5:
        or dword ptr [ecx+35Ch],edx
    L_004495cb:
        mov eax,dword ptr [eax+4]
    L_004495ce:
        test eax,eax
    L_004495d0:
        jne short L_004495c3
    L_004495d2:
        ret
    }
}

// 0x004495E0..0x00449622: ?AnimationManager_ClearFlag@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearFlag_004495e0() {
    __asm {
    L_004495e0:
        mov ecx,dword ptr [eax]
    L_004495e2:
        mov edx,dword ptr [data_00491c10]
    L_004495e8:
        push ecx
    L_004495e9:
        call asm_AnimationManager_Find_004491c0
    L_004495ee:
        test eax,eax
    L_004495f0:
        je short L_00449622
    L_004495f2:
        mov ecx,dword ptr [eax+35Ch]
    L_004495f8:
        mov edx,0FFFFFFFDh
    L_004495fd:
        and ecx,edx
    L_004495ff:
        mov dword ptr [eax+35Ch],ecx
    L_00449605:
        mov ecx,dword ptr [eax+18h]
    L_00449608:
        test ecx,ecx
    L_0044960a:
        jne short L_00449622
    L_0044960c:
        mov eax,dword ptr [eax+14h]
    L_0044960f:
        test eax,eax
    L_00449611:
        je short L_00449622
    L_00449613:
        mov ecx,dword ptr [eax]
    L_00449615:
        and dword ptr [ecx+35Ch],edx
    L_0044961b:
        mov eax,dword ptr [eax+4]
    L_0044961e:
        test eax,eax
    L_00449620:
        jne short L_00449613
    L_00449622:
        ret
    }
}

// 0x00449630..0x00449644: ?AnimationManager_MarkForRemovalAndClearHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkForRemovalAndClearHandle_00449630() {
    __asm {
    L_00449630:
        mov eax,dword ptr [esi]
    L_00449632:
        mov edx,dword ptr [data_00491c10]
    L_00449638:
        push eax
    L_00449639:
        call asm_AnimationManager_SetFlag_004492a0
    L_0044963e:
        mov dword ptr [esi],0
    L_00449644:
        ret
    }
}

// 0x00449670..0x00449693: ?AnimationManager_SelectSpriteFromCurrentResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SelectSpriteFromCurrentResource_00449670() {
    __asm {
    L_00449670:
        mov ecx,dword ptr [eax]
    L_00449672:
        mov edx,dword ptr [data_00491c10]
    L_00449678:
        push ecx
    L_00449679:
        call asm_AnimationManager_Find_004491c0
    L_0044967e:
        test eax,eax
    L_00449680:
        je short L_00449691
    L_00449682:
        mov edx,dword ptr [esp+4]
    L_00449686:
        mov ecx,dword ptr [eax+308h]
    L_0044968c:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00449691:
        ret 4
    }
}

// 0x004496A0..0x004496C1: ?AnimationManager_SelectSpriteFromResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SelectSpriteFromResource_004496a0() {
    __asm {
    L_004496a0:
        mov ecx,dword ptr [eax]
    L_004496a2:
        mov edx,dword ptr [data_00491c10]
    L_004496a8:
        push ecx
    L_004496a9:
        call asm_AnimationManager_Find_004491c0
    L_004496ae:
        test eax,eax
    L_004496b0:
        je short L_004496bf
    L_004496b2:
        mov edx,dword ptr [esp+8]
    L_004496b6:
        mov ecx,dword ptr [esp+4]
    L_004496ba:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004496bf:
        ret 8
    }
}

// 0x004496D0..0x004496F3: FUN_004496d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004496d0_004496d0() {
    __asm {
    L_004496d0:
        mov ecx,dword ptr [eax]
    L_004496d2:
        mov edx,dword ptr [data_00491c10]
    L_004496d8:
        push ecx
    L_004496d9:
        call asm_AnimationManager_Find_004491c0
    L_004496de:
        test eax,eax
    L_004496e0:
        je short L_004496f1
    L_004496e2:
        mov ecx,dword ptr [esp+4]
    L_004496e6:
        mov edx,dword ptr [eax+308h]
    L_004496ec:
        call asm_AnimationObject_ChangeScript_0043e8b0
    L_004496f1:
        ret 4
    }
}

// 0x004497D0..0x00449815: ?AnimationManager_FindChildByScriptIndex@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_FindChildByScriptIndex_004497d0() {
    __asm {
    L_004497d0:
        mov eax,dword ptr [esi]
    L_004497d2:
        mov edx,dword ptr [data_00491c10]
    L_004497d8:
        push eax
    L_004497d9:
        call asm_AnimationManager_Find_004491c0
    L_004497de:
        test eax,eax
    L_004497e0:
        jne short L_004497e4
    L_004497e2:
        mov dword ptr [esi],eax
    L_004497e4:
        add eax,10h
    L_004497e7:
        je short L_00449804
    L_004497e9:
        lea esp,[esp+force_disp32_zero]
    L_004497f0:
        mov ecx,dword ptr [eax]
    L_004497f2:
        movsx edx,word ptr [ecx+38Ah]
    L_004497f9:
        cmp edx,ebx
    L_004497fb:
        je short L_0044980d
    L_004497fd:
        mov eax,dword ptr [eax+4]
    L_00449800:
        test eax,eax
    L_00449802:
        jne short L_004497f0
    L_00449804:
        mov dword ptr [edi],0
    L_0044980a:
        mov eax,edi
    L_0044980c:
        ret
    L_0044980d:
        mov eax,dword ptr [eax]
    L_0044980f:
        mov ecx,dword ptr [eax]
    L_00449811:
        mov dword ptr [edi],ecx
    L_00449813:
        mov eax,edi
    L_00449815:
        ret
    }
}

// 0x00449870..0x00449948: FUN_00449870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449870_00449870() {
    __asm {
    L_00449870:
        sub esp,0Ch
    L_00449873:
        mov edx,dword ptr [esp+10h]
    L_00449877:
        push esi
    L_00449878:
        push edi
    L_00449879:
        mov dword ptr [esp+8],0
    L_00449881:
        mov edi,dword ptr [esp+8]
    L_00449885:
        lea esi,[edx+340h]
    L_0044988b:
        mov dword ptr [esi],edi
    L_0044988d:
        mov dword ptr [esp+0Ch],0
    L_00449895:
        mov edi,dword ptr [esp+0Ch]
    L_00449899:
        mov dword ptr [esi+4],edi
    L_0044989c:
        mov dword ptr [esp+10h],0
    L_004498a4:
        mov edi,dword ptr [esp+10h]
    L_004498a8:
        mov dword ptr [esi+8],edi
    L_004498ab:
        mov dword ptr [esp+8],0
    L_004498b3:
        mov edi,dword ptr [esp+8]
    L_004498b7:
        lea esi,[edx+334h]
    L_004498bd:
        mov dword ptr [esi],edi
    L_004498bf:
        mov dword ptr [esp+0Ch],0
    L_004498c7:
        mov edi,dword ptr [esp+0Ch]
    L_004498cb:
        mov dword ptr [esi+4],edi
    L_004498ce:
        mov dword ptr [esp+10h],0
    L_004498d6:
        mov edi,dword ptr [esp+10h]
    L_004498da:
        mov dword ptr [esi+8],edi
    L_004498dd:
        mov eax,ecx
    L_004498df:
        mov ecx,dword ptr [edx+35Ch]
    L_004498e5:
        lea esi,[edx+34Ch]
    L_004498eb:
        mov dword ptr [esp+8],0
    L_004498f3:
        mov edi,dword ptr [esp+8]
    L_004498f7:
        mov dword ptr [esi],edi
    L_004498f9:
        or ecx,40000000h
    L_004498ff:
        mov dword ptr [esp+0Ch],0
    L_00449907:
        mov edi,dword ptr [esp+0Ch]
    L_0044990b:
        mov dword ptr [esi+4],edi
    L_0044990e:
        mov dword ptr [edx+35Ch],ecx
    L_00449914:
        mov ecx,dword ptr [esp+1Ch]
    L_00449918:
        mov dword ptr [esp+10h],0
    L_00449920:
        mov edi,dword ptr [esp+10h]
    L_00449924:
        mov word ptr [edx+38Ah],cx
    L_0044992b:
        mov dword ptr [esi+8],edi
    L_0044992e:
        mov byte ptr [edx+3A1h],10h
    L_00449935:
        mov byte ptr [edx+3A0h],10h
    L_0044993c:
        call asm_AnimationObject_LoadScriptPreservingState_0043e7e0
    L_00449941:
        pop edi
    L_00449942:
        pop esi
    L_00449943:
        add esp,0Ch
    L_00449946:
        ret 8
    }
}

// 0x00449950..0x004499F0: FUN_00449950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449950_00449950() {
    __asm {
    L_00449950:
        mov eax,dword ptr [esi+3AD068h]
    L_00449956:
        mov ecx,eax
    L_00449958:
        imul ecx,3ACh
    L_0044995e:
        push edi
    L_0044995f:
        lea edi,[ecx+esi+68h]
    L_00449963:
        mov cl,byte ptr [eax+esi+3AC068h]
    L_0044996a:
        test cl,cl
    L_0044996c:
        je short L_004499ca
    L_0044996e:
        inc eax
    L_0044996f:
        and eax,80000FFFh
    L_00449974:
        jns short L_0044997d
    L_00449976:
        dec eax
    L_00449977:
        or eax,0FFFFF000h
    L_0044997c:
        inc eax
    L_0044997d:
        mov edx,eax
    L_0044997f:
        imul edx,3ACh
    L_00449985:
        mov dword ptr [esi+3AD068h],eax
    L_0044998b:
        mov cl,byte ptr [eax+esi+3AC068h]
    L_00449992:
        test cl,cl
    L_00449994:
        lea edi,[edx+esi+68h]
    L_00449998:
        je short L_004499ca
    L_0044999a:
        push 3ACh
    L_0044999f:
        call asm_operator_new_00452493
    L_004499a4:
        add esp,4
    L_004499a7:
        test eax,eax
    L_004499a9:
        je short L_004499bd
    L_004499ab:
        mov ecx,eax
    L_004499ad:
        call asm_Entity_Constructor_00402050
    L_004499b2:
        mov edx,eax
    L_004499b4:
        mov edi,eax
    L_004499b6:
        call asm_InitializeEntity_00401de0
    L_004499bb:
        jmp short L_004499d2
    L_004499bd:
        xor eax,eax
    L_004499bf:
        mov edx,eax
    L_004499c1:
        mov edi,eax
    L_004499c3:
        call asm_InitializeEntity_00401de0
    L_004499c8:
        jmp short L_004499d2
    L_004499ca:
        mov byte ptr [eax+esi+3AC068h],1
    L_004499d2:
        mov eax,dword ptr [esi+3AD068h]
    L_004499d8:
        inc eax
    L_004499d9:
        and eax,80000FFFh
    L_004499de:
        jns short L_004499e7
    L_004499e0:
        dec eax
    L_004499e1:
        or eax,0FFFFF000h
    L_004499e6:
        inc eax
    L_004499e7:
        mov dword ptr [esi+3AD068h],eax
    L_004499ed:
        mov eax,edi
    L_004499ef:
        pop edi
    L_004499f0:
        ret
    }
}
