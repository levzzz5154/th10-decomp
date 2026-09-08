#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413A20..0x00413B40: FUN_00413a20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413a20_00413a20() {
    __asm {
    L_00413a20:
        mov eax,dword ptr [data_00477848]
    L_00413a25:
        mov ecx,dword ptr [eax+20h]
    L_00413a28:
        mov edx,dword ptr [data_00491c10]
    L_00413a2e:
        push ebx
    L_00413a2f:
        push ebp
    L_00413a30:
        mov ebp,dword ptr [esp+0Ch]
    L_00413a34:
        push ecx
    L_00413a35:
        mov ecx,1Ch
    L_00413a3a:
        call asm_Recovery_LoadCachedResource_00447280
    L_00413a3f:
        xor ebx,ebx
    L_00413a41:
        cmp eax,ebx
    L_00413a43:
        mov dword ptr [ebp+9E80h],eax
    L_00413a49:
        je asm_target_00413b27
    L_00413a4f:
        mov eax,dword ptr [data_00491be8]
    L_00413a54:
        cmp eax,ebx
    L_00413a56:
        je short L_00413acb
    L_00413a58:
        mov dword ptr [ebp+9EBCh],eax
    L_00413a5e:
        mov dword ptr [data_00491be8],ebx
    L_00413a64:
        mov eax,dword ptr [ebp+9E70h]
    L_00413a6a:
        test al,1
    L_00413a6c:
        jne short L_00413a97
    L_00413a6e:
        or eax,1
    L_00413a71:
        mov dword ptr [ebp+9E64h],ebx
    L_00413a77:
        mov dword ptr [ebp+9E60h],0FFF0BDC1h
    L_00413a81:
        mov dword ptr [ebp+9E68h],ebx
    L_00413a87:
        mov dword ptr [ebp+9E6Ch],476F78h
    L_00413a91:
        mov dword ptr [ebp+9E70h],eax
    L_00413a97:
        mov dword ptr [ebp+9E64h],ebx
    L_00413a9d:
        mov dword ptr [ebp+9E68h],ebx
    L_00413aa3:
        or eax,0FFFFFFFFh
    L_00413aa6:
        mov dword ptr [ebp+9E60h],eax
    L_00413aac:
        mov ecx,dword ptr [data_00474c44]
    L_00413ab2:
        mov dword ptr [ebp+9EC0h],eax
    L_00413ab8:
        mov dword ptr [ebp+9EC4h],eax
    L_00413abe:
        mov dword ptr [ebp+9E78h],ecx
    L_00413ac4:
        pop ebp
    L_00413ac5:
        xor eax,eax
    L_00413ac7:
        pop ebx
    L_00413ac8:
        ret 4
    L_00413acb:
        mov edx,dword ptr [data_00477848]
    L_00413ad1:
        mov eax,dword ptr [data_00474c68]
    L_00413ad6:
        mov eax,dword ptr [edx+eax*4+18h]
    L_00413ada:
        mov byte ptr [data_00497c38],bl
    L_00413ae0:
        mov ecx,eax
    L_00413ae2:
        mov dl,byte ptr [eax]
    L_00413ae4:
        inc eax
    L_00413ae5:
        cmp dl,bl
    L_00413ae7:
        jne short L_00413ae2
    L_00413ae9:
        push esi
    L_00413aea:
        push edi
    L_00413aeb:
        mov edi,497C38h
    L_00413af0:
        sub eax,ecx
    L_00413af2:
        mov esi,ecx
    L_00413af4:
        dec edi
    L_00413af5:
        mov cl,byte ptr [edi+1]
    L_00413af8:
        inc edi
    L_00413af9:
        cmp cl,bl
    L_00413afb:
        jne short L_00413af5
    L_00413afd:
        mov ecx,eax
    L_00413aff:
        shr ecx,2
    L_00413b02:
        rep movsd
    L_00413b04:
        mov ecx,eax
    L_00413b06:
        push ebx
    L_00413b07:
        and ecx,3
    L_00413b0a:
        push ebx
    L_00413b0b:
        mov eax,497C38h
    L_00413b10:
        rep movsb
    L_00413b12:
        call asm_FUN_0044b360_0044b360
    L_00413b17:
        cmp eax,ebx
    L_00413b19:
        pop edi
    L_00413b1a:
        mov dword ptr [ebp+9EBCh],eax
    L_00413b20:
        pop esi
    L_00413b21:
        jne asm_target_00413a64
    L_00413b27:
        push 46CB68h
    L_00413b2c:
        mov ecx,474F70h
    L_00413b31:
        call asm_TextLog_Append_0044b810
    L_00413b36:
        add esp,4
    L_00413b39:
        pop ebp
    L_00413b3a:
        or eax,0FFFFFFFFh
    L_00413b3d:
        pop ebx
    L_00413b3e:
        ret 4
    }
}

// 0x0041C330..0x0041C441: FUN_0041c330
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c330_0041c330() {
    __asm {
    L_0041c330:
        push esi
    L_0041c331:
        mov esi,dword ptr [edi+18h]
    L_0041c334:
        test esi,esi
    L_0041c336:
        je asm_target_0041c43b
    L_0041c33c:
        push ebx
    L_0041c33d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041c340:
        mov al,byte ptr [esi+50h]
    L_0041c343:
        test al,al
    L_0041c345:
        mov ebx,dword ptr [esi+8]
    L_0041c348:
        je short L_0041c359
    L_0041c34a:
        inc al
    L_0041c34c:
        cmp al,2
    L_0041c34e:
        mov byte ptr [esi+50h],al
    L_0041c351:
        jb short L_0041c359
    L_0041c353:
        mov eax,dword ptr [esi]
    L_0041c355:
        mov ecx,esi
    L_0041c357:
        jmp short L_0041c363
    L_0041c359:
        cmp dword ptr [esi+0Ch],1
    L_0041c35d:
        mov eax,dword ptr [esi]
    L_0041c35f:
        mov ecx,esi
    L_0041c361:
        jne short L_0041c3a1
    L_0041c363:
        call dword ptr [eax+10h]
    L_0041c366:
        dec dword ptr [edi+438h]
    L_0041c36c:
        mov edx,dword ptr [esi+8]
    L_0041c36f:
        mov ecx,dword ptr [esi+4]
    L_0041c372:
        mov dword ptr [ecx+8],edx
    L_0041c375:
        mov eax,dword ptr [esi+8]
    L_0041c378:
        test eax,eax
    L_0041c37a:
        je short L_0041c382
    L_0041c37c:
        mov ecx,dword ptr [esi+4]
    L_0041c37f:
        mov dword ptr [eax+4],ecx
    L_0041c382:
        cmp dword ptr [edi+434h],esi
    L_0041c388:
        jne short L_0041c393
    L_0041c38a:
        mov edx,dword ptr [esi+4]
    L_0041c38d:
        mov dword ptr [edi+434h],edx
    L_0041c393:
        push esi
    L_0041c394:
        call asm_free_004524a1
    L_0041c399:
        add esp,4
    L_0041c39c:
        jmp asm_target_0041c430
    L_0041c3a1:
        call dword ptr [eax+8]
    L_0041c3a4:
        test eax,eax
    L_0041c3a6:
        je short L_0041c3e7
    L_0041c3a8:
        mov edx,dword ptr [esi]
    L_0041c3aa:
        mov ecx,esi
    L_0041c3ac:
        call dword ptr [edx+10h]
    L_0041c3af:
        dec dword ptr [edi+438h]
    L_0041c3b5:
        mov eax,dword ptr [esi+4]
    L_0041c3b8:
        mov ecx,dword ptr [esi+8]
    L_0041c3bb:
        mov dword ptr [eax+8],ecx
    L_0041c3be:
        mov eax,dword ptr [esi+8]
    L_0041c3c1:
        test eax,eax
    L_0041c3c3:
        je short L_0041c3cb
    L_0041c3c5:
        mov edx,dword ptr [esi+4]
    L_0041c3c8:
        mov dword ptr [eax+4],edx
    L_0041c3cb:
        cmp dword ptr [edi+434h],esi
    L_0041c3d1:
        jne short L_0041c3dc
    L_0041c3d3:
        mov eax,dword ptr [esi+4]
    L_0041c3d6:
        mov dword ptr [edi+434h],eax
    L_0041c3dc:
        push esi
    L_0041c3dd:
        call asm_free_004524a1
    L_0041c3e2:
        add esp,4
    L_0041c3e5:
        jmp short L_0041c430
    L_0041c3e7:
        mov edx,dword ptr [esi+14h]
    L_0041c3ea:
        mov ecx,dword ptr [esi+1Ch]
    L_0041c3ed:
        mov dword ptr [esi+10h],edx
    L_0041c3f0:
        fld dword ptr [ecx]
    L_0041c3f2:
        fcomp dword ptr [data_00470b68]
    L_0041c3f8:
        fnstsw ax
    L_0041c3fa:
        test ah,41h
    L_0041c3fd:
        jne short L_0041c420
    L_0041c3ff:
        fld dword ptr [ecx]
    L_0041c401:
        fcomp dword ptr [data_00470b64]
    L_0041c407:
        fnstsw ax
    L_0041c409:
        test ah,5
    L_0041c40c:
        jp short L_0041c420
    L_0041c40e:
        fld dword ptr [esi+18h]
    L_0041c411:
        inc edx
    L_0041c412:
        fadd dword ptr [data_00470afc]
    L_0041c418:
        mov dword ptr [esi+14h],edx
    L_0041c41b:
        fstp dword ptr [esi+18h]
    L_0041c41e:
        jmp short L_0041c430
    L_0041c420:
        fld dword ptr [ecx]
    L_0041c422:
        fadd dword ptr [esi+18h]
    L_0041c425:
        fst dword ptr [esi+18h]
    L_0041c428:
        call asm_FUN_00463b2c_00463b2c
    L_0041c42d:
        mov dword ptr [esi+14h],eax
    L_0041c430:
        test ebx,ebx
    L_0041c432:
        mov esi,ebx
    L_0041c434:
        jne asm_target_0041c340
    L_0041c43a:
        pop ebx
    L_0041c43b:
        mov eax,1
    L_0041c440:
        pop esi
    L_0041c441:
        ret
    }
}

// 0x0042AF20..0x0042AF80: FUN_0042af20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042af20_0042af20() {
    __asm {
    L_0042af20:
        push 0FFFFFFFFh
    L_0042af22:
        push 4655ABh
    L_0042af27:
        mov eax,dword ptr fs:[0]
    L_0042af2d:
        push eax
    L_0042af2e:
        mov dword ptr fs:[0],esp
    L_0042af35:
        push ecx
    L_0042af36:
        push 1DCB4h
    L_0042af3b:
        call asm_operator_new_00452493
    L_0042af40:
        add esp,4
    L_0042af43:
        mov dword ptr [esp],eax
    L_0042af46:
        test eax,eax
    L_0042af48:
        mov dword ptr [esp+0Ch],0
    L_0042af50:
        je short L_0042af6b
    L_0042af52:
        call asm_EffectManager_InitializePoolsRetail_0042ae60
    L_0042af57:
        mov dword ptr [data_0047783c],eax
    L_0042af5c:
        mov ecx,dword ptr [esp+4]
    L_0042af60:
        mov dword ptr fs:[0],ecx
    L_0042af67:
        add esp,10h
    L_0042af6a:
        ret
    L_0042af6b:
        mov ecx,dword ptr [esp+4]
    L_0042af6f:
        xor eax,eax
    L_0042af71:
        mov dword ptr [data_0047783c],eax
    L_0042af76:
        mov dword ptr fs:[0],ecx
    L_0042af7d:
        add esp,10h
    L_0042af80:
        ret
    }
}
