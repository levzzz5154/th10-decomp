#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ItemManager_DestroyRetail_00405f70() {
    __asm {
    L_00405f70:
        mov eax,dword ptr fs:[0]
    L_00405f76:
        push 0FFFFFFFFh
    L_00405f78:
        push 46553Ch
    L_00405f7d:
        push eax
    L_00405f7e:
        mov dword ptr fs:[0],esp
    L_00405f85:
        push ebx
    L_00405f86:
        push ebp
    L_00405f87:
        push esi
    L_00405f88:
        push edi
    L_00405f89:
        mov dword ptr [esp+18h],0
    L_00405f91:
        mov eax,dword ptr [esp+20h]
    L_00405f95:
        mov esi,dword ptr [eax+8]
    L_00405f98:
        test esi,esi
    L_00405f9a:
        mov edi,dword ptr [data_00491be4]
    L_00405fa0:
        mov ebx,dword ptr [data_004660b0]
    L_00405fa6:
        mov ebp,dword ptr [data_004660b4]
    L_00405fac:
        je short L_00405fd1
    L_00405fae:
        push 492274h
    L_00405fb3:
        call ebx
    L_00405fb5:
        inc byte ptr [data_0049231c]
    L_00405fbb:
        mov ecx,esi
    L_00405fbd:
        mov edx,edi
    L_00405fbf:
        call asm_Scheduler_Remove_00449f60
    L_00405fc4:
        push 492274h
    L_00405fc9:
        call ebp
    L_00405fcb:
        dec byte ptr [data_0049231c]
    L_00405fd1:
        mov ecx,dword ptr [esp+20h]
    L_00405fd5:
        mov esi,dword ptr [ecx+0Ch]
    L_00405fd8:
        test esi,esi
    L_00405fda:
        mov edi,dword ptr [data_00491be4]
    L_00405fe0:
        je short L_00406005
    L_00405fe2:
        push 492274h
    L_00405fe7:
        call ebx
    L_00405fe9:
        inc byte ptr [data_0049231c]
    L_00405fef:
        mov ecx,esi
    L_00405ff1:
        mov edx,edi
    L_00405ff3:
        call asm_Scheduler_Remove_00449f60
    L_00405ff8:
        push 492274h
    L_00405ffd:
        call ebp
    L_00405fff:
        dec byte ptr [data_0049231c]
    L_00406005:
        mov edx,dword ptr [esp+20h]
    L_00406009:
        mov edx,dword ptr [edx+3E0B50h]
    L_0040600f:
        mov eax,dword ptr [data_00491c10]
    L_00406014:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00406019:
        push 405DE0h
    L_0040601e:
        mov dword ptr [esp+1Ch],0FFFFFFFFh
    L_00406026:
        mov eax,dword ptr [esp+24h]
    L_0040602a:
        push 7D1h
    L_0040602f:
        push 7F0h
    L_00406034:
        add eax,60h
    L_00406037:
        push eax
    L_00406038:
        mov dword ptr [data_004776f0],0
    L_00406042:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00406047:
        mov ecx,dword ptr [esp+10h]
    L_0040604b:
        pop edi
    L_0040604c:
        pop esi
    L_0040604d:
        pop ebp
    L_0040604e:
        mov dword ptr fs:[0],ecx
    L_00406055:
        pop ebx
    L_00406056:
        add esp,0Ch
    L_00406059:
        ret 4
    }
}

// 0x00408AF0..0x00408C81: FUN_00408af0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408af0_00408af0() {
    __asm {
    L_00408af0:
        push 0FFFFFFFFh
    L_00408af2:
        push 46560Fh
    L_00408af7:
        mov eax,dword ptr fs:[0]
    L_00408afd:
        push eax
    L_00408afe:
        mov dword ptr fs:[0],esp
    L_00408b05:
        push ecx
    L_00408b06:
        push ebx
    L_00408b07:
        push ebp
    L_00408b08:
        push esi
    L_00408b09:
        mov esi,dword ptr [esp+20h]
    L_00408b0d:
        push edi
    L_00408b0e:
        mov dword ptr [esp+1Ch],2
    L_00408b16:
        mov eax,dword ptr [esi+768h]
    L_00408b1c:
        mov edi,dword ptr [data_00491c10]
    L_00408b22:
        push eax
    L_00408b23:
        mov edx,edi
    L_00408b25:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b2a:
        xor ebx,ebx
    L_00408b2c:
        mov dword ptr [esi+768h],ebx
    L_00408b32:
        mov ecx,dword ptr [esi+76Ch]
    L_00408b38:
        push ecx
    L_00408b39:
        mov edx,edi
    L_00408b3b:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b40:
        mov dword ptr [esi+76Ch],ebx
    L_00408b46:
        mov edx,dword ptr [esi+770h]
    L_00408b4c:
        push edx
    L_00408b4d:
        mov edx,edi
    L_00408b4f:
        call asm_AnimationManager_SetFlag_004492a0
    L_00408b54:
        mov ebp,dword ptr [data_00491be4]
    L_00408b5a:
        mov dword ptr [esi+770h],ebx
    L_00408b60:
        mov edi,dword ptr [esi+8]
    L_00408b63:
        cmp edi,ebx
    L_00408b65:
        mov ebx,dword ptr [data_004660b0]
    L_00408b6b:
        je short L_00408b98
    L_00408b6d:
        push 492274h
    L_00408b72:
        call ebx
    L_00408b74:
        inc byte ptr [data_0049231c]
    L_00408b7a:
        mov ecx,edi
    L_00408b7c:
        mov edx,ebp
    L_00408b7e:
        call asm_Scheduler_Remove_00449f60
    L_00408b83:
        mov ebp,dword ptr [data_004660b4]
    L_00408b89:
        push 492274h
    L_00408b8e:
        call ebp
    L_00408b90:
        dec byte ptr [data_0049231c]
    L_00408b96:
        jmp short L_00408b9e
    L_00408b98:
        mov ebp,dword ptr [data_004660b4]
    L_00408b9e:
        mov edi,dword ptr [esi+0Ch]
    L_00408ba1:
        test edi,edi
    L_00408ba3:
        mov eax,dword ptr [data_00491be4]
    L_00408ba8:
        mov dword ptr [esp+10h],eax
    L_00408bac:
        je short L_00408bd3
    L_00408bae:
        push 492274h
    L_00408bb3:
        call ebx
    L_00408bb5:
        inc byte ptr [data_0049231c]
    L_00408bbb:
        mov edx,dword ptr [esp+10h]
    L_00408bbf:
        mov ecx,edi
    L_00408bc1:
        call asm_Scheduler_Remove_00449f60
    L_00408bc6:
        push 492274h
    L_00408bcb:
        call ebp
    L_00408bcd:
        dec byte ptr [data_0049231c]
    L_00408bd3:
        mov edi,dword ptr [esi+37ACh]
    L_00408bd9:
        test edi,edi
    L_00408bdb:
        mov ecx,dword ptr [data_00491be4]
    L_00408be1:
        mov dword ptr [esp+10h],ecx
    L_00408be5:
        je short L_00408c0c
    L_00408be7:
        push 492274h
    L_00408bec:
        call ebx
    L_00408bee:
        inc byte ptr [data_0049231c]
    L_00408bf4:
        mov edx,dword ptr [esp+10h]
    L_00408bf8:
        mov ecx,edi
    L_00408bfa:
        call asm_Scheduler_Remove_00449f60
    L_00408bff:
        push 492274h
    L_00408c04:
        call ebp
    L_00408c06:
        dec byte ptr [data_0049231c]
    L_00408c0c:
        push 401FF0h
    L_00408c11:
        push 5
    L_00408c13:
        push 3ACh
    L_00408c18:
        lea edx,[esi+24D8h]
    L_00408c1e:
        push edx
    L_00408c1f:
        mov dword ptr [data_004776f4],0
    L_00408c29:
        mov byte ptr [esp+2Ch],1
    L_00408c2e:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c33:
        push 401FF0h
    L_00408c38:
        push 8
    L_00408c3a:
        push 3ACh
    L_00408c3f:
        lea eax,[esi+778h]
    L_00408c45:
        push eax
    L_00408c46:
        mov byte ptr [esp+2Ch],0
    L_00408c4b:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c50:
        push 401FF0h
    L_00408c55:
        push 2
    L_00408c57:
        push 3ACh
    L_00408c5c:
        add esi,10h
    L_00408c5f:
        push esi
    L_00408c60:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00408c68:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00408c6d:
        mov ecx,dword ptr [esp+14h]
    L_00408c71:
        pop edi
    L_00408c72:
        pop esi
    L_00408c73:
        pop ebp
    L_00408c74:
        pop ebx
    L_00408c75:
        mov dword ptr fs:[0],ecx
    L_00408c7c:
        add esp,10h
    L_00408c7f:
        ret 4
    }
}

// 0x00409F90..0x0040A005: FUN_00409f90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f90_00409f90() {
    __asm {
    L_00409f90:
        push ebx
    L_00409f91:
        mov ebx,dword ptr [data_00491c10]
    L_00409f97:
        push ebp
    L_00409f98:
        mov ebp,dword ptr [esp+0Ch]
    L_00409f9c:
        push esi
    L_00409f9d:
        push edi
    L_00409f9e:
        lea esi,[ebx+3AD090h]
    L_00409fa4:
        mov edi,4
    L_00409fa9:
        lea esp,[esp+force_disp32_zero]
    L_00409fb0:
        mov edx,dword ptr [esi]
    L_00409fb2:
        mov eax,ebx
    L_00409fb4:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00409fb9:
        add esi,4
    L_00409fbc:
        dec edi
    L_00409fbd:
        jne short L_00409fb0
    L_00409fbf:
        mov eax,dword ptr [ebp+58h]
    L_00409fc2:
        xor edi,edi
    L_00409fc4:
        cmp eax,edi
    L_00409fc6:
        je short L_00409fe0
    L_00409fc8:
        mov esi,dword ptr [eax+4]
    L_00409fcb:
        mov eax,dword ptr [eax]
    L_00409fcd:
        cmp eax,edi
    L_00409fcf:
        je short L_00409fda
    L_00409fd1:
        mov edx,dword ptr [eax]
    L_00409fd3:
        push 1
    L_00409fd5:
        mov ecx,eax
    L_00409fd7:
        call dword ptr [edx+14h]
    L_00409fda:
        cmp esi,edi
    L_00409fdc:
        mov eax,esi
    L_00409fde:
        jne short L_00409fc8
    L_00409fe0:
        mov eax,dword ptr [ebp+8]
    L_00409fe3:
        cmp eax,edi
    L_00409fe5:
        mov dword ptr [ebp+64h],edi
    L_00409fe8:
        mov dword ptr [ebp+10h],edi
    L_00409feb:
        mov ecx,0FFFFFFFDh
    L_00409ff0:
        je short L_00409ff5
    L_00409ff2:
        and dword ptr [eax+4],ecx
    L_00409ff5:
        mov eax,dword ptr [ebp+0Ch]
    L_00409ff8:
        cmp eax,edi
    L_00409ffa:
        pop edi
    L_00409ffb:
        pop esi
    L_00409ffc:
        pop ebp
    L_00409ffd:
        pop ebx
    L_00409ffe:
        je short L_0040a003
    L_0040a000:
        and dword ptr [eax+4],ecx
    L_0040a003:
        ret 4
    }
}

// 0x0040B7B0..0x0040B919: FUN_0040b7b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b7b0_0040b7b0() {
    __asm {
    L_0040b7b0:
        mov eax,dword ptr [esp+4]
    L_0040b7b4:
        push ebx
    L_0040b7b5:
        mov ebx,dword ptr [data_004660b0]
    L_0040b7bb:
        push ebp
    L_0040b7bc:
        mov ebp,dword ptr [data_004660b4]
    L_0040b7c2:
        push esi
    L_0040b7c3:
        mov esi,dword ptr [eax+8]
    L_0040b7c6:
        test esi,esi
    L_0040b7c8:
        push edi
    L_0040b7c9:
        mov edi,dword ptr [data_00491be4]
    L_0040b7cf:
        je short L_0040b7f4
    L_0040b7d1:
        push 492274h
    L_0040b7d6:
        call ebx
    L_0040b7d8:
        inc byte ptr [data_0049231c]
    L_0040b7de:
        mov ecx,esi
    L_0040b7e0:
        mov edx,edi
    L_0040b7e2:
        call asm_Scheduler_Remove_00449f60
    L_0040b7e7:
        push 492274h
    L_0040b7ec:
        call ebp
    L_0040b7ee:
        dec byte ptr [data_0049231c]
    L_0040b7f4:
        mov ecx,dword ptr [esp+14h]
    L_0040b7f8:
        mov esi,dword ptr [ecx+0Ch]
    L_0040b7fb:
        test esi,esi
    L_0040b7fd:
        mov edi,dword ptr [data_00491be4]
    L_0040b803:
        je short L_0040b828
    L_0040b805:
        push 492274h
    L_0040b80a:
        call ebx
    L_0040b80c:
        inc byte ptr [data_0049231c]
    L_0040b812:
        mov ecx,esi
    L_0040b814:
        mov edx,edi
    L_0040b816:
        call asm_Scheduler_Remove_00449f60
    L_0040b81b:
        push 492274h
    L_0040b820:
        call ebp
    L_0040b822:
        dec byte ptr [data_0049231c]
    L_0040b828:
        mov edi,dword ptr [data_00491c10]
    L_0040b82e:
        xor esi,esi
    L_0040b830:
        call asm_AnimationManager_ClearIndexedResources_00447f70
    L_0040b835:
        mov ebp,dword ptr [esp+14h]
    L_0040b839:
        mov esi,dword ptr [ebp+18h]
    L_0040b83c:
        xor ebx,ebx
    L_0040b83e:
        cmp esi,ebx
    L_0040b840:
        je short L_0040b852
    L_0040b842:
        mov eax,esi
    L_0040b844:
        call asm_FUN_0040b3a0_0040b3a0
    L_0040b849:
        push esi
    L_0040b84a:
        call asm_free_004524a1
    L_0040b84f:
        add esp,4
    L_0040b852:
        mov esi,dword ptr [data_00491c10]
    L_0040b858:
        add esi,3AD0E0h
    L_0040b85e:
        mov dword ptr [ebp+18h],ebx
    L_0040b861:
        mov edi,dword ptr [esi]
    L_0040b863:
        cmp edi,ebx
    L_0040b865:
        je short L_0040b879
    L_0040b867:
        call asm_FUN_00447810_00447810
    L_0040b86c:
        mov edx,dword ptr [esi]
    L_0040b86e:
        push edx
    L_0040b86f:
        call asm_free_004524a1
    L_0040b874:
        add esp,4
    L_0040b877:
        mov dword ptr [esi],ebx
    L_0040b879:
        mov esi,dword ptr [data_00491c10]
    L_0040b87f:
        mov edi,dword ptr [esi+3AD0E4h]
    L_0040b885:
        add esi,3AD0E4h
    L_0040b88b:
        cmp edi,ebx
    L_0040b88d:
        je short L_0040b8a1
    L_0040b88f:
        call asm_FUN_00447810_00447810
    L_0040b894:
        mov eax,dword ptr [esi]
    L_0040b896:
        push eax
    L_0040b897:
        call asm_free_004524a1
    L_0040b89c:
        add esp,4
    L_0040b89f:
        mov dword ptr [esi],ebx
    L_0040b8a1:
        mov esi,dword ptr [data_00491c10]
    L_0040b8a7:
        mov edi,dword ptr [esi+3AD0E8h]
    L_0040b8ad:
        add esi,3AD0E8h
    L_0040b8b3:
        cmp edi,ebx
    L_0040b8b5:
        je short L_0040b8c9
    L_0040b8b7:
        call asm_FUN_00447810_00447810
    L_0040b8bc:
        mov ecx,dword ptr [esi]
    L_0040b8be:
        push ecx
    L_0040b8bf:
        call asm_free_004524a1
    L_0040b8c4:
        add esp,4
    L_0040b8c7:
        mov dword ptr [esi],ebx
    L_0040b8c9:
        mov esi,dword ptr [data_00491c10]
    L_0040b8cf:
        mov edi,dword ptr [esi+3AD0ECh]
    L_0040b8d5:
        add esi,3AD0ECh
    L_0040b8db:
        cmp edi,ebx
    L_0040b8dd:
        je short L_0040b8f1
    L_0040b8df:
        call asm_FUN_00447810_00447810
    L_0040b8e4:
        mov edx,dword ptr [esi]
    L_0040b8e6:
        push edx
    L_0040b8e7:
        call asm_free_004524a1
    L_0040b8ec:
        add esp,4
    L_0040b8ef:
        mov dword ptr [esi],ebx
    L_0040b8f1:
        mov eax,dword ptr [ebp+14h]
    L_0040b8f4:
        cmp eax,ebx
    L_0040b8f6:
        je short L_0040b904
    L_0040b8f8:
        push eax
    L_0040b8f9:
        call asm_free_00452422
    L_0040b8fe:
        add esp,4
    L_0040b901:
        mov dword ptr [ebp+14h],ebx
    L_0040b904:
        pop edi
    L_0040b905:
        pop esi
    L_0040b906:
        mov dword ptr [ebp+14h],ebx
    L_0040b909:
        pop ebp
    L_0040b90a:
        mov dword ptr [data_00477700],ebx
    L_0040b910:
        mov dword ptr [data_004918a4],ebx
    L_0040b916:
        pop ebx
    L_0040b917:
        ret 4
    }
}

// 0x0040D530..0x0040D65B: FUN_0040d530
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d530_0040d530() {
    __asm {
    L_0040d530:
        push ecx
    L_0040d531:
        push ebx
    L_0040d532:
        push ebp
    L_0040d533:
        push esi
    L_0040d534:
        push edi
    L_0040d535:
        mov edi,eax
    L_0040d537:
        push edi
    L_0040d538:
        call asm_FUN_00409f90_00409f90
    L_0040d53d:
        mov esi,dword ptr [edi+8]
    L_0040d540:
        test esi,esi
    L_0040d542:
        mov ebx,dword ptr [data_00491be4]
    L_0040d548:
        mov ebp,dword ptr [data_004660b0]
    L_0040d54e:
        je short L_0040d577
    L_0040d550:
        push 492274h
    L_0040d555:
        call ebp
    L_0040d557:
        inc byte ptr [data_0049231c]
    L_0040d55d:
        mov ecx,esi
    L_0040d55f:
        mov edx,ebx
    L_0040d561:
        call asm_Scheduler_Remove_00449f60
    L_0040d566:
        push 492274h
    L_0040d56b:
        call dword ptr [data_004660b4]
    L_0040d571:
        dec byte ptr [data_0049231c]
    L_0040d577:
        mov esi,dword ptr [edi+0Ch]
    L_0040d57a:
        test esi,esi
    L_0040d57c:
        mov ebx,dword ptr [data_00491be4]
    L_0040d582:
        je short L_0040d5ab
    L_0040d584:
        push 492274h
    L_0040d589:
        call ebp
    L_0040d58b:
        inc byte ptr [data_0049231c]
    L_0040d591:
        mov ecx,esi
    L_0040d593:
        mov edx,ebx
    L_0040d595:
        call asm_Scheduler_Remove_00449f60
    L_0040d59a:
        push 492274h
    L_0040d59f:
        call dword ptr [data_004660b4]
    L_0040d5a5:
        dec byte ptr [data_0049231c]
    L_0040d5ab:
        mov esi,0Ch
    L_0040d5b0:
        mov eax,dword ptr [edi+54h]
    L_0040d5b3:
        mov eax,dword ptr [esi+eax]
    L_0040d5b6:
        test eax,eax
    L_0040d5b8:
        je short L_0040d5c3
    L_0040d5ba:
        push eax
    L_0040d5bb:
        call asm_free_00452422
    L_0040d5c0:
        add esp,4
    L_0040d5c3:
        add esi,4
    L_0040d5c6:
        cmp esi,8Ch
    L_0040d5cc:
        jl short L_0040d5b0
    L_0040d5ce:
        mov esi,dword ptr [edi+54h]
    L_0040d5d1:
        test esi,esi
    L_0040d5d3:
        je short L_0040d5e3
    L_0040d5d5:
        call asm_BulletEntity_ReleaseResource_0040d680
    L_0040d5da:
        push esi
    L_0040d5db:
        call asm_free_004524a1
    L_0040d5e0:
        add esp,4
    L_0040d5e3:
        xor eax,eax
    L_0040d5e5:
        mov dword ptr [edi+54h],eax
    L_0040d5e8:
        test byte ptr [data_00474ca0],9
    L_0040d5ef:
        jne short L_0040d651
    L_0040d5f1:
        mov ebp,9
    L_0040d5f6:
        mov ebx,3AD090h
    L_0040d5fb:
        mov dword ptr [esp+10h],4
    L_0040d603:
        test ebp,ebp
    L_0040d605:
        jl short L_0040d632
    L_0040d607:
        cmp ebp,21h
    L_0040d60a:
        jae short L_0040d632
    L_0040d60c:
        mov ecx,dword ptr [data_00491c10]
    L_0040d612:
        mov edi,dword ptr [ebx+ecx]
    L_0040d615:
        test edi,edi
    L_0040d617:
        lea esi,[ebx+ecx]
    L_0040d61a:
        je short L_0040d632
    L_0040d61c:
        call asm_FUN_00447810_00447810
    L_0040d621:
        mov edx,dword ptr [esi]
    L_0040d623:
        push edx
    L_0040d624:
        call asm_free_004524a1
    L_0040d629:
        add esp,4
    L_0040d62c:
        mov dword ptr [esi],0
    L_0040d632:
        mov eax,dword ptr [esp+10h]
    L_0040d636:
        add ebx,4
    L_0040d639:
        inc ebp
    L_0040d63a:
        dec eax
    L_0040d63b:
        mov dword ptr [esp+10h],eax
    L_0040d63f:
        jne short L_0040d603
    L_0040d641:
        pop edi
    L_0040d642:
        pop esi
    L_0040d643:
        pop ebp
    L_0040d644:
        mov dword ptr [data_00477704],0
    L_0040d64e:
        pop ebx
    L_0040d64f:
        pop ecx
    L_0040d650:
        ret
    L_0040d651:
        pop edi
    L_0040d652:
        pop esi
    L_0040d653:
        pop ebp
    L_0040d654:
        mov dword ptr [data_00477704],eax
    L_0040d659:
        pop ebx
    L_0040d65a:
        pop ecx
    L_0040d65b:
        ret
    }
}

// 0x00414370..0x0041451C: FUN_00414370
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414370_00414370() {
    __asm {
    L_00414370:
        mov al,byte ptr [data_00474ca0]
    L_00414375:
        push ebx
    L_00414376:
        push ebp
    L_00414377:
        mov ebp,dword ptr [esp+0Ch]
    L_0041437b:
        push esi
    L_0041437c:
        xor ebx,ebx
    L_0041437e:
        test al,9
    L_00414380:
        push edi
    L_00414381:
        jne short L_004143ad
    L_00414383:
        mov esi,dword ptr [data_00491c10]
    L_00414389:
        mov edi,dword ptr [esi+3AD0DCh]
    L_0041438f:
        add esi,3AD0DCh
    L_00414395:
        cmp edi,ebx
    L_00414397:
        je short L_004143bd
    L_00414399:
        call asm_FUN_00447810_00447810
    L_0041439e:
        mov eax,dword ptr [esi]
    L_004143a0:
        push eax
    L_004143a1:
        call asm_free_004524a1
    L_004143a6:
        add esp,4
    L_004143a9:
        mov dword ptr [esi],ebx
    L_004143ab:
        jmp short L_004143bd
    L_004143ad:
        mov edx,dword ptr [ebp+9E80h]
    L_004143b3:
        mov eax,dword ptr [data_00491c10]
    L_004143b8:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_004143bd:
        mov esi,dword ptr [ebp+9EB8h]
    L_004143c3:
        cmp esi,ebx
    L_004143c5:
        mov dword ptr [ebp+9E80h],ebx
    L_004143cb:
        je short L_004143e1
    L_004143cd:
        call asm_AnimationSlot_ReleaseRetail_004136c0
    L_004143d2:
        push esi
    L_004143d3:
        call asm_free_004524a1
    L_004143d8:
        add esp,4
    L_004143db:
        mov dword ptr [ebp+9EB8h],ebx
    L_004143e1:
        test byte ptr [data_00474ca0],9
    L_004143e8:
        jne short L_00414411
    L_004143ea:
        mov eax,dword ptr [ebp+9EBCh]
    L_004143f0:
        cmp eax,ebx
    L_004143f2:
        je short L_00414403
    L_004143f4:
        push eax
    L_004143f5:
        call asm_free_00452422
    L_004143fa:
        add esp,4
    L_004143fd:
        mov dword ptr [ebp+9EBCh],ebx
    L_00414403:
        mov dword ptr [ebp+9EBCh],ebx
    L_00414409:
        mov dword ptr [data_00491be8],ebx
    L_0041440f:
        jmp short L_0041441d
    L_00414411:
        mov ecx,dword ptr [ebp+9EBCh]
    L_00414417:
        mov dword ptr [data_00491be8],ecx
    L_0041441d:
        mov eax,dword ptr [ebp+8]
    L_00414420:
        cmp eax,ebx
    L_00414422:
        je short L_00414428
    L_00414424:
        and dword ptr [eax+4],0FFFFFFFDh
    L_00414428:
        mov edx,dword ptr [ebp+9E14h]
    L_0041442e:
        push edx
    L_0041442f:
        mov edx,dword ptr [data_00491c10]
    L_00414435:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041443a:
        mov esi,dword ptr [data_00491c10]
    L_00414440:
        mov dword ptr [ebp+9E14h],ebx
    L_00414446:
        mov eax,dword ptr [ebp+9E18h]
    L_0041444c:
        push eax
    L_0041444d:
        mov edx,esi
    L_0041444f:
        call asm_AnimationManager_SetFlag_004492a0
    L_00414454:
        mov dword ptr [ebp+9E18h],ebx
    L_0041445a:
        mov ecx,dword ptr [ebp+9E24h]
    L_00414460:
        push ecx
    L_00414461:
        mov edx,esi
    L_00414463:
        call asm_AnimationManager_SetFlag_004492a0
    L_00414468:
        xor edx,edx
    L_0041446a:
        mov dword ptr [ebp+9E24h],ebx
    L_00414470:
        mov dword ptr [ebp+9E28h],edx
    L_00414476:
        mov dword ptr [ebp+9E2Ch],edx
    L_0041447c:
        mov dword ptr [ebp+9E30h],edx
    L_00414482:
        mov dword ptr [ebp+9E34h],edx
    L_00414488:
        mov dword ptr [ebp+9E38h],edx
    L_0041448e:
        mov dword ptr [ebp+9E3Ch],edx
    L_00414494:
        mov dword ptr [ebp+9E40h],edx
    L_0041449a:
        mov dword ptr [ebp+9E44h],edx
    L_004144a0:
        mov dword ptr [ebp+9E48h],edx
    L_004144a6:
        mov dword ptr [ebp+9E4Ch],edx
    L_004144ac:
        lea edx,[ebp+9DF4h]
    L_004144b2:
        mov dword ptr [esp+14h],8
    L_004144ba:
        lea ebx,[ebx+force_disp32_zero]
    L_004144c0:
        mov ecx,dword ptr [edx]
    L_004144c2:
        cmp ecx,ebx
    L_004144c4:
        TH10_REL8(0x74, 0x004144c4, VA_asm_target_0041452f)
    L_004144c6:
        mov eax,dword ptr [esi+72DAD4h]
    L_004144cc:
        cmp eax,ebx
    L_004144ce:
        je short L_004144dd
    L_004144d0:
        mov edi,dword ptr [eax]
    L_004144d2:
        cmp dword ptr [edi],ecx
    L_004144d4:
        je short L_004144f6
    L_004144d6:
        mov eax,dword ptr [eax+4]
    L_004144d9:
        cmp eax,ebx
    L_004144db:
        jne short L_004144d0
    L_004144dd:
        mov eax,dword ptr [esi+72DADCh]
    L_004144e3:
        cmp eax,ebx
    L_004144e5:
        TH10_REL8(0x74, 0x004144e5, VA_asm_target_0041452f)
    L_004144e7:
        mov edi,dword ptr [eax]
    L_004144e9:
        cmp dword ptr [edi],ecx
    L_004144eb:
        je short L_004144f6
    L_004144ed:
        mov eax,dword ptr [eax+4]
    L_004144f0:
        cmp eax,ebx
    L_004144f2:
        jne short L_004144e7
    L_004144f4:
        TH10_REL8(0xeb, 0x004144f4, VA_asm_target_0041452f)
    L_004144f6:
        mov eax,dword ptr [eax]
    L_004144f8:
        cmp eax,ebx
    L_004144fa:
        TH10_REL8(0x74, 0x004144fa, VA_asm_target_0041452f)
    L_004144fc:
        mov ecx,dword ptr [eax+35Ch]
    L_00414502:
        mov edi,4000000h
    L_00414507:
        or ecx,edi
    L_00414509:
        mov dword ptr [eax+35Ch],ecx
    L_0041450f:
        cmp dword ptr [eax+18h],ebx
    L_00414512:
        TH10_REL8(0x75, 0x00414512, VA_asm_target_0041452f)
    L_00414514:
        mov eax,dword ptr [eax+14h]
    L_00414517:
        cmp eax,ebx
    L_00414519:
        TH10_REL8(0x74, 0x00414519, VA_asm_target_0041452f)
    L_0041451b:
        TH10_REL8(0xeb, 0x0041451b, VA_asm_FUN_00414370_part_00414520)
    }
}

// 0x00414520..0x0041454B: FUN_00414370
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414370_part_00414520() {
    __asm {
    L_00414520:
        mov ecx,dword ptr [eax]
    L_00414522:
        or dword ptr [ecx+35Ch],edi
    L_00414528:
        mov eax,dword ptr [eax+4]
    L_0041452b:
        cmp eax,ebx
    L_0041452d:
        jne short L_00414520
    L_0041452f:
        mov eax,dword ptr [esp+14h]
    L_00414533:
        mov dword ptr [edx],ebx
    L_00414535:
        add edx,4
    L_00414538:
        dec eax
    L_00414539:
        mov dword ptr [esp+14h],eax
    L_0041453d:
        TH10_REL8(0x75, 0x0041453d, VA_asm_target_004144c0)
    L_0041453f:
        pop edi
    L_00414540:
        pop esi
    L_00414541:
        mov dword ptr [ebp+9E90h],ebx
    L_00414547:
        pop ebp
    L_00414548:
        pop ebx
    L_00414549:
        ret 4
    }
}

// 0x004145F0..0x004146BC: FUN_004145f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004145f0_004145f0() {
    __asm {
    L_004145f0:
        push 0FFFFFFFFh
    L_004145f2:
        push 46574Eh
    L_004145f7:
        mov eax,dword ptr fs:[0]
    L_004145fd:
        push eax
    L_004145fe:
        mov dword ptr fs:[0],esp
    L_00414605:
        push ecx
    L_00414606:
        push ebx
    L_00414607:
        push ebp
    L_00414608:
        push esi
    L_00414609:
        mov esi,dword ptr [esp+20h]
    L_0041460d:
        push edi
    L_0041460e:
        push esi
    L_0041460f:
        mov dword ptr [esp+20h],6
    L_00414617:
        call asm_FUN_00414370_00414370
    L_0041461c:
        mov edi,dword ptr [esi+8]
    L_0041461f:
        test edi,edi
    L_00414621:
        mov ebp,dword ptr [data_00491be4]
    L_00414627:
        mov ebx,dword ptr [data_004660b0]
    L_0041462d:
        je short L_00414656
    L_0041462f:
        push 492274h
    L_00414634:
        call ebx
    L_00414636:
        inc byte ptr [data_0049231c]
    L_0041463c:
        mov ecx,edi
    L_0041463e:
        mov edx,ebp
    L_00414640:
        call asm_Scheduler_Remove_00449f60
    L_00414645:
        push 492274h
    L_0041464a:
        call dword ptr [data_004660b4]
    L_00414650:
        dec byte ptr [data_0049231c]
    L_00414656:
        mov edi,dword ptr [esi+0Ch]
    L_00414659:
        test edi,edi
    L_0041465b:
        mov ebp,dword ptr [data_00491be4]
    L_00414661:
        je short L_0041468a
    L_00414663:
        push 492274h
    L_00414668:
        call ebx
    L_0041466a:
        inc byte ptr [data_0049231c]
    L_00414670:
        mov ecx,edi
    L_00414672:
        mov edx,ebp
    L_00414674:
        call asm_Scheduler_Remove_00449f60
    L_00414679:
        push 492274h
    L_0041467e:
        call dword ptr [data_004660b4]
    L_00414684:
        dec byte ptr [data_0049231c]
    L_0041468a:
        mov ebp,dword ptr [data_00491c10]
    L_00414690:
        mov dword ptr [esi+8],0
    L_00414697:
        mov eax,dword ptr [esi+9E50h]
    L_0041469d:
        push eax
    L_0041469e:
        mov edx,ebp
    L_004146a0:
        call asm_AnimationManager_SetFlag_004492a0
    L_004146a5:
        xor edi,edi
    L_004146a7:
        mov dword ptr [esi+9E50h],edi
    L_004146ad:
        lea ebx,[esi+9DF4h]
    L_004146b3:
        mov dword ptr [esp+10h],8
    L_004146bb:
        TH10_REL8(0xeb, 0x004146bb, VA_asm_FUN_004145f0_part_004146c0)
    }
}

// 0x004146C0..0x0041471C: FUN_004145f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004145f0_part_004146c0() {
    __asm {
    L_004146c0:
        mov edx,dword ptr [ebx]
    L_004146c2:
        cmp edx,edi
    L_004146c4:
        TH10_REL8(0x74, 0x004146c4, VA_asm_target_0041472f)
    L_004146c6:
        mov eax,dword ptr [ebp+72DAD4h]
    L_004146cc:
        cmp eax,edi
    L_004146ce:
        je short L_004146dd
    L_004146d0:
        mov ecx,dword ptr [eax]
    L_004146d2:
        cmp dword ptr [ecx],edx
    L_004146d4:
        je short L_004146f6
    L_004146d6:
        mov eax,dword ptr [eax+4]
    L_004146d9:
        cmp eax,edi
    L_004146db:
        jne short L_004146d0
    L_004146dd:
        mov eax,dword ptr [ebp+72DADCh]
    L_004146e3:
        cmp eax,edi
    L_004146e5:
        TH10_REL8(0x74, 0x004146e5, VA_asm_target_0041472f)
    L_004146e7:
        mov ecx,dword ptr [eax]
    L_004146e9:
        cmp dword ptr [ecx],edx
    L_004146eb:
        je short L_004146f6
    L_004146ed:
        mov eax,dword ptr [eax+4]
    L_004146f0:
        cmp eax,edi
    L_004146f2:
        jne short L_004146e7
    L_004146f4:
        TH10_REL8(0xeb, 0x004146f4, VA_asm_target_0041472f)
    L_004146f6:
        mov eax,dword ptr [eax]
    L_004146f8:
        cmp eax,edi
    L_004146fa:
        TH10_REL8(0x74, 0x004146fa, VA_asm_target_0041472f)
    L_004146fc:
        mov ecx,dword ptr [eax+35Ch]
    L_00414702:
        mov edx,4000000h
    L_00414707:
        or ecx,edx
    L_00414709:
        mov dword ptr [eax+35Ch],ecx
    L_0041470f:
        cmp dword ptr [eax+18h],edi
    L_00414712:
        TH10_REL8(0x75, 0x00414712, VA_asm_target_0041472f)
    L_00414714:
        mov eax,dword ptr [eax+14h]
    L_00414717:
        cmp eax,edi
    L_00414719:
        TH10_REL8(0x74, 0x00414719, VA_asm_target_0041472f)
    L_0041471b:
        TH10_REL8(0xeb, 0x0041471b, VA_asm_FUN_004145f0_part_00414720)
    }
}

// 0x00414720..0x0041482D: FUN_004145f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004145f0_part_00414720() {
    __asm {
    L_00414720:
        mov ecx,dword ptr [eax]
    L_00414722:
        or dword ptr [ecx+35Ch],edx
    L_00414728:
        mov eax,dword ptr [eax+4]
    L_0041472b:
        cmp eax,edi
    L_0041472d:
        jne short L_00414720
    L_0041472f:
        mov eax,dword ptr [esp+10h]
    L_00414733:
        mov dword ptr [ebx],edi
    L_00414735:
        add ebx,4
    L_00414738:
        dec eax
    L_00414739:
        mov dword ptr [esp+10h],eax
    L_0041473d:
        TH10_REL8(0x75, 0x0041473d, VA_asm_FUN_004145f0_part_004146c0)
    L_0041473f:
        mov edx,dword ptr [esi+9EC8h]
    L_00414745:
        mov eax,ebp
    L_00414747:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_0041474c:
        mov eax,dword ptr [esi+9DA0h]
    L_00414752:
        cmp eax,edi
    L_00414754:
        mov dword ptr [data_0047770c],edi
    L_0041475a:
        je short L_00414765
    L_0041475c:
        push eax
    L_0041475d:
        call asm_free_00452422
    L_00414762:
        add esp,4
    L_00414765:
        push 401FF0h
    L_0041476a:
        push 7
    L_0041476c:
        push 3ACh
    L_00414771:
        lea ecx,[esi+8094h]
    L_00414777:
        push ecx
    L_00414778:
        mov dword ptr [esi+9DA0h],edi
    L_0041477e:
        mov byte ptr [esp+2Ch],4
    L_00414783:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00414788:
        push 401FF0h
    L_0041478d:
        push 2
    L_0041478f:
        push 3ACh
    L_00414794:
        lea edx,[esi+793Ch]
    L_0041479a:
        push edx
    L_0041479b:
        mov byte ptr [esp+2Ch],3
    L_004147a0:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147a5:
        push 401FF0h
    L_004147aa:
        push 4
    L_004147ac:
        push 3ACh
    L_004147b1:
        lea eax,[esi+6A8Ch]
    L_004147b7:
        push eax
    L_004147b8:
        mov byte ptr [esp+2Ch],2
    L_004147bd:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147c2:
        push 401FF0h
    L_004147c7:
        push 9
    L_004147c9:
        push 3ACh
    L_004147ce:
        lea ecx,[esi+4980h]
    L_004147d4:
        push ecx
    L_004147d5:
        mov byte ptr [esp+2Ch],1
    L_004147da:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147df:
        push 401FF0h
    L_004147e4:
        push 0Ah
    L_004147e6:
        push 3ACh
    L_004147eb:
        lea edx,[esi+24C8h]
    L_004147f1:
        push edx
    L_004147f2:
        mov byte ptr [esp+2Ch],0
    L_004147f7:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004147fc:
        push 401FF0h
    L_00414801:
        push 0Ah
    L_00414803:
        push 3ACh
    L_00414808:
        add esi,10h
    L_0041480b:
        push esi
    L_0041480c:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00414814:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00414819:
        mov ecx,dword ptr [esp+14h]
    L_0041481d:
        pop edi
    L_0041481e:
        pop esi
    L_0041481f:
        pop ebp
    L_00414820:
        pop ebx
    L_00414821:
        mov dword ptr fs:[0],ecx
    L_00414828:
        add esp,10h
    L_0041482b:
        ret 4
    }
}

// 0x00417C80..0x004180D0: FUN_00417c80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417c80_00417c80() {
    __asm {
    L_00417c80:
        sub esp,10h
    L_00417c83:
        push ebx
    L_00417c84:
        mov ebx,dword ptr [data_0047783c]
    L_00417c8a:
        push ebp
    L_00417c8b:
        push esi
    L_00417c8c:
        push edi
    L_00417c8d:
        call asm_FUN_0042b1e0_0042b1e0
    L_00417c92:
        mov edx,dword ptr [data_00474ca0]
    L_00417c98:
        mov eax,dword ptr [data_00491fb8]
    L_00417c9d:
        and edx,0FFFFFFFCh
    L_00417ca0:
        cmp eax,0Ah
    L_00417ca3:
        mov dword ptr [data_00474ca0],edx
    L_00417ca9:
        mov dword ptr [data_00476f78],3F800000h
    L_00417cb3:
        mov ebx,2
    L_00417cb8:
        jne short L_00417d26
    L_00417cba:
        mov ecx,dword ptr [data_004776e0]
    L_00417cc0:
        mov edx,dword ptr [ecx+89A4h]
    L_00417cc6:
        test edx,edx
    L_00417cc8:
        lea esi,[ecx+89A4h]
    L_00417cce:
        mov dword ptr [esp+14h],43F00000h
    L_00417cd6:
        mov dword ptr [esp+18h],43C40000h
    L_00417cde:
        mov dword ptr [esp+1Ch],0
    L_00417ce6:
        jne short L_00417d08
    L_00417ce8:
        mov eax,dword ptr [ecx+8994h]
    L_00417cee:
        push 6
    L_00417cf0:
        lea ecx,[esp+14h]
    L_00417cf4:
        push ecx
    L_00417cf5:
        push eax
    L_00417cf6:
        lea edi,[esp+20h]
    L_00417cfa:
        call asm_AnimationManager_CreatePositionedPrimary_00448d50
    L_00417cff:
        mov edx,dword ptr [eax]
    L_00417d01:
        mov dword ptr [esi],edx
    L_00417d03:
        mov eax,dword ptr [data_00491fb8]
    L_00417d08:
        mov ecx,dword ptr [data_00474c80]
    L_00417d0e:
        cmp ecx,dword ptr [data_00474c7c]
    L_00417d14:
        jne asm_target_00417db5
    L_00417d1a:
        or dword ptr [data_00474ca0],1
    L_00417d21:
        jmp asm_target_00417db5
    L_00417d26:
        cmp eax,0Bh
    L_00417d29:
        jne short L_00417d49
    L_00417d2b:
        mov esi,dword ptr [data_004776e0]
    L_00417d31:
        push 43D00000h
    L_00417d36:
        push 43600000h
    L_00417d3b:
        call asm_FUN_0040c540_0040c540
    L_00417d40:
        mov eax,dword ptr [data_00474ca0]
    L_00417d45:
        or eax,ebx
    L_00417d47:
        jmp short L_00417dab
    L_00417d49:
        cmp eax,4
    L_00417d4c:
        je short L_00417d53
    L_00417d4e:
        cmp eax,0Fh
    L_00417d51:
        jne short L_00417d6a
    L_00417d53:
        mov esi,dword ptr [data_004776e0]
    L_00417d59:
        push 43C40000h
    L_00417d5e:
        push 43F00000h
    L_00417d63:
        call asm_FUN_0040c540_0040c540
    L_00417d68:
        jmp short L_00417db0
    L_00417d6a:
        cmp eax,0Dh
    L_00417d6d:
        jne short L_00417db5
    L_00417d6f:
        mov esi,dword ptr [data_004776e0]
    L_00417d75:
        push 43C40000h
    L_00417d7a:
        push 43F00000h
    L_00417d7f:
        call asm_FUN_0040c540_0040c540
    L_00417d84:
        mov edx,dword ptr [data_00474c80]
    L_00417d8a:
        cmp edx,dword ptr [data_00474c7c]
    L_00417d90:
        je short L_00417da3
    L_00417d92:
        mov eax,474C40h
    L_00417d97:
        call asm_Score_IncrementCounterClampedNine_00418a90
    L_00417d9c:
        or dword ptr [data_00474ca0],8
    L_00417da3:
        mov eax,dword ptr [data_00474ca0]
    L_00417da8:
        or eax,1
    L_00417dab:
        mov dword ptr [data_00474ca0],eax
    L_00417db0:
        mov eax,dword ptr [data_00491fb8]
    L_00417db5:
        test byte ptr [data_00474ca0],bl
    L_00417dbb:
        jne asm_target_00417ee7
    L_00417dc1:
        cmp eax,0Eh
    L_00417dc4:
        je short L_00417de4
    L_00417dc6:
        cmp eax,0Fh
    L_00417dc9:
        je short L_00417de4
    L_00417dcb:
        mov esi,dword ptr [data_00477838]
    L_00417dd1:
        test esi,esi
    L_00417dd3:
        je short L_00417de4
    L_00417dd5:
        push esi
    L_00417dd6:
        call asm_FUN_004294a0_004294a0
    L_00417ddb:
        push esi
    L_00417ddc:
        call asm_free_004524a1
    L_00417de1:
        add esp,4
    L_00417de4:
        mov esi,dword ptr [data_004776e8]
    L_00417dea:
        test esi,esi
    L_00417dec:
        je short L_00417dfd
    L_00417dee:
        push esi
    L_00417def:
        call asm_DestroyGameState_00402440
    L_00417df4:
        push esi
    L_00417df5:
        call asm_free_004524a1
    L_00417dfa:
        add esp,4
    L_00417dfd:
        mov esi,dword ptr [data_004776e4]
    L_00417e03:
        test esi,esi
    L_00417e05:
        je short L_00417e16
    L_00417e07:
        push esi
    L_00417e08:
        call asm_DestroyGameState_00402440
    L_00417e0d:
        push esi
    L_00417e0e:
        call asm_free_004524a1
    L_00417e13:
        add esp,4
    L_00417e16:
        mov esi,dword ptr [data_00477830]
    L_00417e1c:
        test esi,esi
    L_00417e1e:
        je short L_00417e2f
    L_00417e20:
        push esi
    L_00417e21:
        call asm_FUN_00422220_00422220
    L_00417e26:
        push esi
    L_00417e27:
        call asm_free_004524a1
    L_00417e2c:
        add esp,4
    L_00417e2f:
        mov esi,dword ptr [data_0047770c]
    L_00417e35:
        test esi,esi
    L_00417e37:
        je short L_00417e48
    L_00417e39:
        push esi
    L_00417e3a:
        call asm_FUN_004145f0_004145f0
    L_00417e3f:
        push esi
    L_00417e40:
        call asm_free_004524a1
    L_00417e45:
        add esp,4
    L_00417e48:
        mov esi,dword ptr [data_00477834]
    L_00417e4e:
        test esi,esi
    L_00417e50:
        je short L_00417e61
    L_00417e52:
        push esi
    L_00417e53:
        call asm_FUN_00424ed0_00424ed0
    L_00417e58:
        push esi
    L_00417e59:
        call asm_free_004524a1
    L_00417e5e:
        add esp,4
    L_00417e61:
        mov esi,dword ptr [data_004776f0]
    L_00417e67:
        test esi,esi
    L_00417e69:
        je short L_00417e7a
    L_00417e6b:
        push esi
    L_00417e6c:
        call asm_ItemManager_DestroyRetail_00405f70
    L_00417e71:
        push esi
    L_00417e72:
        call asm_free_004524a1
    L_00417e77:
        add esp,4
    L_00417e7a:
        mov esi,dword ptr [data_00477818]
    L_00417e80:
        test esi,esi
    L_00417e82:
        je short L_00417e93
    L_00417e84:
        push esi
    L_00417e85:
        call asm_FUN_0041adf0_0041adf0
    L_00417e8a:
        push esi
    L_00417e8b:
        call asm_free_004524a1
    L_00417e90:
        add esp,4
    L_00417e93:
        mov esi,dword ptr [data_0047781c]
    L_00417e99:
        test esi,esi
    L_00417e9b:
        je short L_00417eac
    L_00417e9d:
        push esi
    L_00417e9e:
        call asm_ScoreExtendedObject_DestroyRetail_0041c1c0
    L_00417ea3:
        push esi
    L_00417ea4:
        call asm_free_004524a1
    L_00417ea9:
        add esp,4
    L_00417eac:
        mov esi,dword ptr [data_00477814]
    L_00417eb2:
        test esi,esi
    L_00417eb4:
        je short L_00417ec5
    L_00417eb6:
        push esi
    L_00417eb7:
        call asm_FUN_00418ee0_00418ee0
    L_00417ebc:
        push esi
    L_00417ebd:
        call asm_free_004524a1
    L_00417ec2:
        add esp,4
    L_00417ec5:
        mov esi,dword ptr [data_00477840]
    L_00417ecb:
        test esi,esi
    L_00417ecd:
        je asm_target_00417f80
    L_00417ed3:
        push esi
    L_00417ed4:
        call asm_FUN_0042b570_0042b570
    L_00417ed9:
        push esi
    L_00417eda:
        call asm_free_004524a1
    L_00417edf:
        add esp,4
    L_00417ee2:
        jmp asm_target_00417f80
    L_00417ee7:
        mov ebx,dword ptr [data_0047770c]
    L_00417eed:
        call asm_Recovery_ReleaseCompositeState_00414570
    L_00417ef2:
        mov esi,dword ptr [data_004776e4]
    L_00417ef8:
        test esi,esi
    L_00417efa:
        je short L_00417f0b
    L_00417efc:
        push esi
    L_00417efd:
        call asm_DestroyGameState_00402440
    L_00417f02:
        push esi
    L_00417f03:
        call asm_free_004524a1
    L_00417f08:
        add esp,4
    L_00417f0b:
        mov eax,dword ptr [data_004776e8]
    L_00417f10:
        mov dword ptr [data_004776e4],eax
    L_00417f15:
        mov eax,dword ptr [data_00477830]
    L_00417f1a:
        mov ecx,dword ptr [eax+8]
    L_00417f1d:
        test ecx,ecx
    L_00417f1f:
        mov edx,0FFFFFFFDh
    L_00417f24:
        je short L_00417f29
    L_00417f26:
        and dword ptr [ecx+4],edx
    L_00417f29:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f2c:
        test ecx,ecx
    L_00417f2e:
        je short L_00417f35
    L_00417f30:
        mov eax,ecx
    L_00417f32:
        and dword ptr [eax+4],edx
    L_00417f35:
        mov eax,dword ptr [data_004776f0]
    L_00417f3a:
        mov ecx,dword ptr [eax+8]
    L_00417f3d:
        test ecx,ecx
    L_00417f3f:
        je short L_00417f44
    L_00417f41:
        and dword ptr [ecx+4],edx
    L_00417f44:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f47:
        test ecx,ecx
    L_00417f49:
        je short L_00417f50
    L_00417f4b:
        mov eax,ecx
    L_00417f4d:
        and dword ptr [eax+4],edx
    L_00417f50:
        mov eax,dword ptr [data_00477838]
    L_00417f55:
        mov ecx,dword ptr [eax+1CCh]
    L_00417f5b:
        test ecx,ecx
    L_00417f5d:
        je short L_00417f62
    L_00417f5f:
        and dword ptr [ecx+4],edx
    L_00417f62:
        mov ecx,dword ptr [eax+0Ch]
    L_00417f65:
        test ecx,ecx
    L_00417f67:
        je short L_00417f6e
    L_00417f69:
        mov eax,ecx
    L_00417f6b:
        and dword ptr [eax+4],edx
    L_00417f6e:
        mov edi,dword ptr [data_00477818]
    L_00417f74:
        xor eax,eax
    L_00417f76:
        mov ecx,873A8h
    L_00417f7b:
        add edi,14h
    L_00417f7e:
        rep stosd
    L_00417f80:
        test byte ptr [data_00474ca0],9
    L_00417f87:
        jne short L_00417fa5
    L_00417f89:
        mov esi,dword ptr [data_00477704]
    L_00417f8f:
        test esi,esi
    L_00417f91:
        je short L_00417fb1
    L_00417f93:
        mov eax,esi
    L_00417f95:
        call asm_FUN_0040d530_0040d530
    L_00417f9a:
        push esi
    L_00417f9b:
        call asm_free_004524a1
    L_00417fa0:
        add esp,4
    L_00417fa3:
        jmp short L_00417fb1
    L_00417fa5:
        mov ecx,dword ptr [data_00477704]
    L_00417fab:
        push ecx
    L_00417fac:
        call asm_FUN_00409f90_00409f90
    L_00417fb1:
        mov esi,dword ptr [data_004776fc]
    L_00417fb7:
        test esi,esi
    L_00417fb9:
        je short L_00417fca
    L_00417fbb:
        push esi
    L_00417fbc:
        call asm_BulletManager_Release_0040af00
    L_00417fc1:
        push esi
    L_00417fc2:
        call asm_free_004524a1
    L_00417fc7:
        add esp,4
    L_00417fca:
        mov esi,dword ptr [data_004776ec]
    L_00417fd0:
        test esi,esi
    L_00417fd2:
        je short L_00417fe3
    L_00417fd4:
        push esi
    L_00417fd5:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_00417fda:
        push esi
    L_00417fdb:
        call asm_free_004524a1
    L_00417fe0:
        add esp,4
    L_00417fe3:
        mov esi,dword ptr [data_004776f4]
    L_00417fe9:
        test esi,esi
    L_00417feb:
        je short L_00417ffc
    L_00417fed:
        push esi
    L_00417fee:
        call asm_FUN_00408af0_00408af0
    L_00417ff3:
        push esi
    L_00417ff4:
        call asm_free_004524a1
    L_00417ff9:
        add esp,4
    L_00417ffc:
        mov edx,dword ptr [esp+24h]
    L_00418000:
        mov esi,dword ptr [edx+8]
    L_00418003:
        test esi,esi
    L_00418005:
        mov edi,dword ptr [data_00491be4]
    L_0041800b:
        mov ebx,dword ptr [data_004660b0]
    L_00418011:
        mov ebp,dword ptr [data_004660b4]
    L_00418017:
        je short L_0041803c
    L_00418019:
        push 492274h
    L_0041801e:
        call ebx
    L_00418020:
        inc byte ptr [data_0049231c]
    L_00418026:
        mov ecx,esi
    L_00418028:
        mov edx,edi
    L_0041802a:
        call asm_Scheduler_Remove_00449f60
    L_0041802f:
        push 492274h
    L_00418034:
        call ebp
    L_00418036:
        dec byte ptr [data_0049231c]
    L_0041803c:
        mov eax,dword ptr [esp+24h]
    L_00418040:
        mov esi,dword ptr [eax+0Ch]
    L_00418043:
        test esi,esi
    L_00418045:
        mov edi,dword ptr [data_00491be4]
    L_0041804b:
        je short L_00418070
    L_0041804d:
        push 492274h
    L_00418052:
        call ebx
    L_00418054:
        inc byte ptr [data_0049231c]
    L_0041805a:
        mov ecx,esi
    L_0041805c:
        mov edx,edi
    L_0041805e:
        call asm_Scheduler_Remove_00449f60
    L_00418063:
        push 492274h
    L_00418068:
        call ebp
    L_0041806a:
        dec byte ptr [data_0049231c]
    L_00418070:
        test byte ptr [data_00474ca0],22h
    L_00418077:
        pop edi
    L_00418078:
        pop esi
    L_00418079:
        pop ebp
    L_0041807a:
        mov dword ptr [data_00477810],0
    L_00418084:
        pop ebx
    L_00418085:
        jne short L_004180a7
    L_00418087:
        test byte ptr [data_00491d78],10h
    L_0041808e:
        mov edx,46DF98h
    L_00418093:
        push 0
    L_00418095:
        mov eax,492590h
    L_0041809a:
        je short L_004180a0
    L_0041809c:
        push 4
    L_0041809e:
        jmp short L_004180a2
    L_004180a0:
        push 3
    L_004180a2:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004180a7:
        mov eax,dword ptr [data_00474ca0]
    L_004180ac:
        and al,1
    L_004180ae:
        neg al
    L_004180b0:
        mov dword ptr [data_004918a4],1
    L_004180ba:
        sbb eax,eax
    L_004180bc:
        and eax,1000000h
    L_004180c1:
        add eax,0FF000000h
    L_004180c6:
        mov dword ptr [data_004923a8],eax
    L_004180cb:
        add esp,10h
    L_004180ce:
        ret 4
    }
}

// 0x00418EE0..0x00419039: FUN_00418ee0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418ee0_00418ee0() {
    __asm {
    L_00418ee0:
        push ecx
    L_00418ee1:
        mov edx,dword ptr [esp+8]
    L_00418ee5:
        push ebx
    L_00418ee6:
        mov ebx,dword ptr [data_004660b0]
    L_00418eec:
        push ebp
    L_00418eed:
        mov ebp,dword ptr [data_004660b4]
    L_00418ef3:
        push esi
    L_00418ef4:
        mov esi,dword ptr [edx+8]
    L_00418ef7:
        test esi,esi
    L_00418ef9:
        push edi
    L_00418efa:
        mov edi,dword ptr [data_00491be4]
    L_00418f00:
        je short L_00418f2f
    L_00418f02:
        push 492274h
    L_00418f07:
        call ebx
    L_00418f09:
        inc byte ptr [data_0049231c]
    L_00418f0f:
        mov ecx,esi
    L_00418f11:
        mov edx,edi
    L_00418f13:
        call asm_Scheduler_Remove_00449f60
    L_00418f18:
        push 492274h
    L_00418f1d:
        call ebp
    L_00418f1f:
        mov al,byte ptr [data_0049231c]
    L_00418f24:
        mov edx,dword ptr [esp+18h]
    L_00418f28:
        dec al
    L_00418f2a:
        mov byte ptr [data_0049231c],al
    L_00418f2f:
        mov esi,dword ptr [edx+0Ch]
    L_00418f32:
        test esi,esi
    L_00418f34:
        mov edi,dword ptr [data_00491be4]
    L_00418f3a:
        je short L_00418f69
    L_00418f3c:
        push 492274h
    L_00418f41:
        call ebx
    L_00418f43:
        inc byte ptr [data_0049231c]
    L_00418f49:
        mov ecx,esi
    L_00418f4b:
        mov edx,edi
    L_00418f4d:
        call asm_Scheduler_Remove_00449f60
    L_00418f52:
        push 492274h
    L_00418f57:
        call ebp
    L_00418f59:
        mov al,byte ptr [data_0049231c]
    L_00418f5e:
        mov edx,dword ptr [esp+18h]
    L_00418f62:
        dec al
    L_00418f64:
        mov byte ptr [data_0049231c],al
    L_00418f69:
        mov ebx,dword ptr [data_00491c10]
    L_00418f6f:
        lea esi,[edx+0DCh]
    L_00418f75:
        mov dword ptr [esp+10h],0Ah
    L_00418f7d:
        mov edi,4000000h
    L_00418f82:
        mov ecx,dword ptr [esi]
    L_00418f84:
        test ecx,ecx
    L_00418f86:
        je short L_00418ff1
    L_00418f88:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00418f8e:
        test eax,eax
    L_00418f90:
        je short L_00418fa0
    L_00418f92:
        mov ebp,dword ptr [eax]
    L_00418f94:
        cmp dword ptr [ebp],ecx
    L_00418f97:
        je short L_00418fc0
    L_00418f99:
        mov eax,dword ptr [eax+4]
    L_00418f9c:
        test eax,eax
    L_00418f9e:
        jne short L_00418f92
    L_00418fa0:
        mov eax,dword ptr [ebx+72DADCh]
    L_00418fa6:
        test eax,eax
    L_00418fa8:
        je short L_00418ff1
    L_00418faa:
        lea ebx,[ebx+force_disp32_zero]
    L_00418fb0:
        mov ebp,dword ptr [eax]
    L_00418fb2:
        cmp dword ptr [ebp],ecx
    L_00418fb5:
        je short L_00418fc0
    L_00418fb7:
        mov eax,dword ptr [eax+4]
    L_00418fba:
        test eax,eax
    L_00418fbc:
        jne short L_00418fb0
    L_00418fbe:
        jmp short L_00418ff1
    L_00418fc0:
        mov eax,dword ptr [eax]
    L_00418fc2:
        test eax,eax
    L_00418fc4:
        je short L_00418ff1
    L_00418fc6:
        mov ebp,dword ptr [eax+35Ch]
    L_00418fcc:
        mov ecx,dword ptr [eax+18h]
    L_00418fcf:
        or ebp,edi
    L_00418fd1:
        test ecx,ecx
    L_00418fd3:
        mov dword ptr [eax+35Ch],ebp
    L_00418fd9:
        jne short L_00418ff1
    L_00418fdb:
        mov eax,dword ptr [eax+14h]
    L_00418fde:
        test eax,eax
    L_00418fe0:
        je short L_00418ff1
    L_00418fe2:
        mov ecx,dword ptr [eax]
    L_00418fe4:
        or dword ptr [ecx+35Ch],edi
    L_00418fea:
        mov eax,dword ptr [eax+4]
    L_00418fed:
        test eax,eax
    L_00418fef:
        jne short L_00418fe2
    L_00418ff1:
        mov eax,dword ptr [esp+10h]
    L_00418ff5:
        mov dword ptr [esi],0
    L_00418ffb:
        add esi,4
    L_00418ffe:
        dec eax
    L_00418fff:
        mov dword ptr [esp+10h],eax
    L_00419003:
        jne asm_target_00418f82
    L_00419009:
        cmp byte ptr [data_00491d6a],2
    L_00419010:
        pop edi
    L_00419011:
        pop esi
    L_00419012:
        pop ebp
    L_00419013:
        pop ebx
    L_00419014:
        jne short L_00419025
    L_00419016:
        push 46D6D8h
    L_0041901b:
        push edx
    L_0041901c:
        call asm_FUN_0041a200_0041a200
    L_00419021:
        mov edx,dword ptr [esp+8]
    L_00419025:
        mov eax,edx
    L_00419027:
        call asm_Recovery_ClearEightBuckets_00419040
    L_0041902c:
        mov dword ptr [data_00477814],0
    L_00419036:
        pop ecx
    L_00419037:
        ret 4
    }
}

// 0x0041ADF0..0x0041AEC7: FUN_0041adf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041adf0_0041adf0() {
    __asm {
    L_0041adf0:
        mov eax,dword ptr fs:[0]
    L_0041adf6:
        push 0FFFFFFFFh
    L_0041adf8:
        push 46541Ch
    L_0041adfd:
        push eax
    L_0041adfe:
        mov dword ptr fs:[0],esp
    L_0041ae05:
        push ebx
    L_0041ae06:
        push ebp
    L_0041ae07:
        push esi
    L_0041ae08:
        push edi
    L_0041ae09:
        mov dword ptr [esp+18h],0
    L_0041ae11:
        mov eax,dword ptr [esp+20h]
    L_0041ae15:
        mov esi,dword ptr [eax+8]
    L_0041ae18:
        test esi,esi
    L_0041ae1a:
        mov edi,dword ptr [data_00491be4]
    L_0041ae20:
        mov ebx,dword ptr [data_004660b0]
    L_0041ae26:
        mov ebp,dword ptr [data_004660b4]
    L_0041ae2c:
        je short L_0041ae51
    L_0041ae2e:
        push 492274h
    L_0041ae33:
        call ebx
    L_0041ae35:
        inc byte ptr [data_0049231c]
    L_0041ae3b:
        mov ecx,esi
    L_0041ae3d:
        mov edx,edi
    L_0041ae3f:
        call asm_Scheduler_Remove_00449f60
    L_0041ae44:
        push 492274h
    L_0041ae49:
        call ebp
    L_0041ae4b:
        dec byte ptr [data_0049231c]
    L_0041ae51:
        mov ecx,dword ptr [esp+20h]
    L_0041ae55:
        mov esi,dword ptr [ecx+0Ch]
    L_0041ae58:
        test esi,esi
    L_0041ae5a:
        mov edi,dword ptr [data_00491be4]
    L_0041ae60:
        je short L_0041ae85
    L_0041ae62:
        push 492274h
    L_0041ae67:
        call ebx
    L_0041ae69:
        inc byte ptr [data_0049231c]
    L_0041ae6f:
        mov ecx,esi
    L_0041ae71:
        mov edx,edi
    L_0041ae73:
        call asm_Scheduler_Remove_00449f60
    L_0041ae78:
        push 492274h
    L_0041ae7d:
        call ebp
    L_0041ae7f:
        dec byte ptr [data_0049231c]
    L_0041ae85:
        push 41AD60h
    L_0041ae8a:
        mov dword ptr [esp+1Ch],0FFFFFFFFh
    L_0041ae92:
        mov edx,dword ptr [esp+24h]
    L_0041ae96:
        push 896h
    L_0041ae9b:
        push 3F0h
    L_0041aea0:
        add edx,14h
    L_0041aea3:
        push edx
    L_0041aea4:
        mov dword ptr [data_00477818],0
    L_0041aeae:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0041aeb3:
        mov ecx,dword ptr [esp+10h]
    L_0041aeb7:
        pop edi
    L_0041aeb8:
        pop esi
    L_0041aeb9:
        pop ebp
    L_0041aeba:
        mov dword ptr fs:[0],ecx
    L_0041aec1:
        pop ebx
    L_0041aec2:
        add esp,0Ch
    L_0041aec5:
        ret 4
    }
}

// 0x0041FB50..0x0041FCF0: FUN_0041fb50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041fb50_0041fb50() {
    __asm {
    L_0041fb50:
        push 0FFFFFFFFh
    L_0041fb52:
        push 465696h
    L_0041fb57:
        mov eax,dword ptr fs:[0]
    L_0041fb5d:
        push eax
    L_0041fb5e:
        mov dword ptr fs:[0],esp
    L_0041fb65:
        push ecx
    L_0041fb66:
        push ebx
    L_0041fb67:
        push ebp
    L_0041fb68:
        push esi
    L_0041fb69:
        push edi
    L_0041fb6a:
        mov dword ptr [esp+1Ch],1
    L_0041fb72:
        mov edi,dword ptr [esp+24h]
    L_0041fb76:
        lea esi,[edi+10h]
    L_0041fb79:
        mov dword ptr [esp+10h],esi
    L_0041fb7d:
        call asm_Platform_StopWorker_0044c150
    L_0041fb82:
        mov edi,dword ptr [edi+8]
    L_0041fb85:
        test edi,edi
    L_0041fb87:
        mov ebx,dword ptr [data_00491be4]
    L_0041fb8d:
        mov esi,dword ptr [data_004660b0]
    L_0041fb93:
        mov ebp,dword ptr [data_004660b4]
    L_0041fb99:
        je short L_0041fbbe
    L_0041fb9b:
        push 492274h
    L_0041fba0:
        call esi
    L_0041fba2:
        inc byte ptr [data_0049231c]
    L_0041fba8:
        mov ecx,edi
    L_0041fbaa:
        mov edx,ebx
    L_0041fbac:
        call asm_Scheduler_Remove_00449f60
    L_0041fbb1:
        push 492274h
    L_0041fbb6:
        call ebp
    L_0041fbb8:
        dec byte ptr [data_0049231c]
    L_0041fbbe:
        mov eax,dword ptr [esp+24h]
    L_0041fbc2:
        mov edi,dword ptr [eax+0Ch]
    L_0041fbc5:
        test edi,edi
    L_0041fbc7:
        mov ebx,dword ptr [data_00491be4]
    L_0041fbcd:
        je short L_0041fbf2
    L_0041fbcf:
        push 492274h
    L_0041fbd4:
        call esi
    L_0041fbd6:
        inc byte ptr [data_0049231c]
    L_0041fbdc:
        mov ecx,edi
    L_0041fbde:
        mov edx,ebx
    L_0041fbe0:
        call asm_Scheduler_Remove_00449f60
    L_0041fbe5:
        push 492274h
    L_0041fbea:
        call ebp
    L_0041fbec:
        dec byte ptr [data_0049231c]
    L_0041fbf2:
        call asm_Recovery_ReleasePair_0041f930
    L_0041fbf7:
        mov ebx,dword ptr [data_00491c10]
    L_0041fbfd:
        mov edi,dword ptr [ebx+3AD070h]
    L_0041fc03:
        add ebx,3AD070h
    L_0041fc09:
        xor ebp,ebp
    L_0041fc0b:
        cmp edi,ebp
    L_0041fc0d:
        je short L_0041fc21
    L_0041fc0f:
        call asm_FUN_00447810_00447810
    L_0041fc14:
        mov ecx,dword ptr [ebx]
    L_0041fc16:
        push ecx
    L_0041fc17:
        call asm_free_004524a1
    L_0041fc1c:
        add esp,4
    L_0041fc1f:
        mov dword ptr [ebx],ebp
    L_0041fc21:
        mov esi,dword ptr [data_004776e0]
    L_0041fc27:
        cmp esi,ebp
    L_0041fc29:
        mov dword ptr [data_00477820],ebp
    L_0041fc2f:
        je short L_0041fc40
    L_0041fc31:
        push esi
    L_0041fc32:
        call asm_DestroyGameThread_00401260
    L_0041fc37:
        push esi
    L_0041fc38:
        call asm_free_004524a1
    L_0041fc3d:
        add esp,4
    L_0041fc40:
        mov ebx,dword ptr [data_00491c10]
    L_0041fc46:
        mov edi,dword ptr [ebx+3AD06Ch]
    L_0041fc4c:
        add ebx,3AD06Ch
    L_0041fc52:
        cmp edi,ebp
    L_0041fc54:
        je short L_0041fc68
    L_0041fc56:
        call asm_FUN_00447810_00447810
    L_0041fc5b:
        mov edx,dword ptr [ebx]
    L_0041fc5d:
        push edx
    L_0041fc5e:
        call asm_free_004524a1
    L_0041fc63:
        add esp,4
    L_0041fc66:
        mov dword ptr [ebx],ebp
    L_0041fc68:
        mov ebx,dword ptr [data_0047783c]
    L_0041fc6e:
        call asm_FUN_0042b1e0_0042b1e0
    L_0041fc73:
        mov edi,dword ptr [data_0047783c]
    L_0041fc79:
        cmp edi,ebp
    L_0041fc7b:
        je short L_0041fcaa
    L_0041fc7d:
        mov eax,dword ptr [edi]
    L_0041fc7f:
        cmp eax,ebp
    L_0041fc81:
        je short L_0041fc8e
    L_0041fc83:
        push eax
    L_0041fc84:
        call asm_free_00452422
    L_0041fc89:
        add esp,4
    L_0041fc8c:
        mov dword ptr [edi],ebp
    L_0041fc8e:
        mov eax,dword ptr [edi+4]
    L_0041fc91:
        cmp eax,ebp
    L_0041fc93:
        je short L_0041fca1
    L_0041fc95:
        push eax
    L_0041fc96:
        call asm_free_00452422
    L_0041fc9b:
        add esp,4
    L_0041fc9e:
        mov dword ptr [edi+4],ebp
    L_0041fca1:
        push edi
    L_0041fca2:
        call asm_free_004524a1
    L_0041fca7:
        add esp,4
    L_0041fcaa:
        mov esi,dword ptr [esp+24h]
    L_0041fcae:
        mov eax,dword ptr [esi+388h]
    L_0041fcb4:
        cmp eax,ebp
    L_0041fcb6:
        mov dword ptr [data_0047783c],ebp
    L_0041fcbc:
        je short L_0041fcc7
    L_0041fcbe:
        push eax
    L_0041fcbf:
        call asm_free_00452422
    L_0041fcc4:
        add esp,4
    L_0041fcc7:
        mov dword ptr [esi+388h],ebp
    L_0041fccd:
        mov esi,dword ptr [esp+10h]
    L_0041fcd1:
        mov dword ptr [esi],4703E4h
    L_0041fcd7:
        call asm_Platform_StopWorker_0044c150
    L_0041fcdc:
        mov ecx,dword ptr [esp+14h]
    L_0041fce0:
        pop edi
    L_0041fce1:
        pop esi
    L_0041fce2:
        pop ebp
    L_0041fce3:
        pop ebx
    L_0041fce4:
        mov dword ptr fs:[0],ecx
    L_0041fceb:
        add esp,10h
    L_0041fcee:
        ret 4
    }
}

// 0x00422220..0x00422356: FUN_00422220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422220_00422220() {
    __asm {
    L_00422220:
        mov eax,dword ptr [esp+4]
    L_00422224:
        push ebx
    L_00422225:
        mov ebx,dword ptr [data_004660b0]
    L_0042222b:
        push ebp
    L_0042222c:
        mov ebp,dword ptr [data_004660b4]
    L_00422232:
        push esi
    L_00422233:
        mov esi,dword ptr [eax+8]
    L_00422236:
        test esi,esi
    L_00422238:
        push edi
    L_00422239:
        mov edi,dword ptr [data_00491be4]
    L_0042223f:
        je short L_00422264
    L_00422241:
        push 492274h
    L_00422246:
        call ebx
    L_00422248:
        inc byte ptr [data_0049231c]
    L_0042224e:
        mov ecx,esi
    L_00422250:
        mov edx,edi
    L_00422252:
        call asm_Scheduler_Remove_00449f60
    L_00422257:
        push 492274h
    L_0042225c:
        call ebp
    L_0042225e:
        dec byte ptr [data_0049231c]
    L_00422264:
        mov ecx,dword ptr [esp+14h]
    L_00422268:
        mov esi,dword ptr [ecx+0Ch]
    L_0042226b:
        test esi,esi
    L_0042226d:
        mov edi,dword ptr [data_00491be4]
    L_00422273:
        je short L_00422298
    L_00422275:
        push 492274h
    L_0042227a:
        call ebx
    L_0042227c:
        inc byte ptr [data_0049231c]
    L_00422282:
        mov ecx,esi
    L_00422284:
        mov edx,edi
    L_00422286:
        call asm_Scheduler_Remove_00449f60
    L_0042228b:
        push 492274h
    L_00422290:
        call ebp
    L_00422292:
        dec byte ptr [data_0049231c]
    L_00422298:
        mov edi,dword ptr [esp+14h]
    L_0042229c:
        add edi,1ECh
    L_004222a2:
        mov ebx,19h
    L_004222a7:
        mov esi,dword ptr [edi]
    L_004222a9:
        test esi,esi
    L_004222ab:
        je short L_004222bc
    L_004222ad:
        push esi
    L_004222ae:
        call asm_FUN_004294a0_004294a0
    L_004222b3:
        push esi
    L_004222b4:
        call asm_free_004524a1
    L_004222b9:
        add esp,4
    L_004222bc:
        add edi,4
    L_004222bf:
        dec ebx
    L_004222c0:
        jne short L_004222a7
    L_004222c2:
        mov edx,dword ptr [esp+14h]
    L_004222c6:
        mov ecx,dword ptr [edx+1DCh]
    L_004222cc:
        test ecx,ecx
    L_004222ce:
        je short L_0042233f
    L_004222d0:
        mov edx,dword ptr [data_00491c10]
    L_004222d6:
        mov eax,dword ptr [edx+72DAD4h]
    L_004222dc:
        test eax,eax
    L_004222de:
        je short L_004222ed
    L_004222e0:
        mov esi,dword ptr [eax]
    L_004222e2:
        cmp dword ptr [esi],ecx
    L_004222e4:
        je short L_00422306
    L_004222e6:
        mov eax,dword ptr [eax+4]
    L_004222e9:
        test eax,eax
    L_004222eb:
        jne short L_004222e0
    L_004222ed:
        mov eax,dword ptr [edx+72DADCh]
    L_004222f3:
        test eax,eax
    L_004222f5:
        je short L_0042233f
    L_004222f7:
        mov edx,dword ptr [eax]
    L_004222f9:
        cmp dword ptr [edx],ecx
    L_004222fb:
        je short L_00422306
    L_004222fd:
        mov eax,dword ptr [eax+4]
    L_00422300:
        test eax,eax
    L_00422302:
        jne short L_004222f7
    L_00422304:
        jmp short L_0042233f
    L_00422306:
        mov eax,dword ptr [eax]
    L_00422308:
        test eax,eax
    L_0042230a:
        je short L_0042233f
    L_0042230c:
        mov esi,dword ptr [eax+35Ch]
    L_00422312:
        mov ecx,dword ptr [eax+18h]
    L_00422315:
        mov edx,4000000h
    L_0042231a:
        or esi,edx
    L_0042231c:
        test ecx,ecx
    L_0042231e:
        mov dword ptr [eax+35Ch],esi
    L_00422324:
        jne short L_0042233f
    L_00422326:
        mov eax,dword ptr [eax+14h]
    L_00422329:
        test eax,eax
    L_0042232b:
        je short L_0042233f
    L_0042232d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00422330:
        mov ecx,dword ptr [eax]
    L_00422332:
        or dword ptr [ecx+35Ch],edx
    L_00422338:
        mov eax,dword ptr [eax+4]
    L_0042233b:
        test eax,eax
    L_0042233d:
        jne short L_00422330
    L_0042233f:
        mov ecx,dword ptr [esp+14h]
    L_00422343:
        pop edi
    L_00422344:
        pop esi
    L_00422345:
        xor eax,eax
    L_00422347:
        pop ebp
    L_00422348:
        mov dword ptr [ecx+1DCh],eax
    L_0042234e:
        mov dword ptr [data_00477830],eax
    L_00422353:
        pop ebx
    L_00422354:
        ret 4
    }
}

// 0x00424ED0..0x00425014: FUN_00424ed0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424ed0_00424ed0() {
    __asm {
    L_00424ed0:
        mov eax,dword ptr fs:[0]
    L_00424ed6:
        push 0FFFFFFFFh
    L_00424ed8:
        push 46528Bh
    L_00424edd:
        push eax
    L_00424ede:
        mov dword ptr fs:[0],esp
    L_00424ee5:
        push ebx
    L_00424ee6:
        mov ebx,dword ptr [esp+14h]
    L_00424eea:
        push ebp
    L_00424eeb:
        push esi
    L_00424eec:
        push edi
    L_00424eed:
        mov dword ptr [esp+18h],0
    L_00424ef5:
        mov esi,dword ptr [ebx+8]
    L_00424ef8:
        test esi,esi
    L_00424efa:
        mov edi,dword ptr [data_00491be4]
    L_00424f00:
        mov ebp,dword ptr [data_004660b0]
    L_00424f06:
        je short L_00424f2f
    L_00424f08:
        push 492274h
    L_00424f0d:
        call ebp
    L_00424f0f:
        inc byte ptr [data_0049231c]
    L_00424f15:
        mov ecx,esi
    L_00424f17:
        mov edx,edi
    L_00424f19:
        call asm_Scheduler_Remove_00449f60
    L_00424f1e:
        push 492274h
    L_00424f23:
        call dword ptr [data_004660b4]
    L_00424f29:
        dec byte ptr [data_0049231c]
    L_00424f2f:
        mov esi,dword ptr [ebx+0Ch]
    L_00424f32:
        test esi,esi
    L_00424f34:
        mov edi,dword ptr [data_00491be4]
    L_00424f3a:
        je short L_00424f63
    L_00424f3c:
        push 492274h
    L_00424f41:
        call ebp
    L_00424f43:
        inc byte ptr [data_0049231c]
    L_00424f49:
        mov ecx,esi
    L_00424f4b:
        mov edx,edi
    L_00424f4d:
        call asm_Scheduler_Remove_00449f60
    L_00424f52:
        push 492274h
    L_00424f57:
        call dword ptr [data_004660b4]
    L_00424f5d:
        dec byte ptr [data_0049231c]
    L_00424f63:
        test byte ptr [data_00474ca0],1
    L_00424f6a:
        mov dword ptr [data_00477834],0
    L_00424f74:
        je short L_00424f90
    L_00424f76:
        mov edx,dword ptr [ebx+10h]
    L_00424f79:
        mov eax,dword ptr [data_00491c10]
    L_00424f7e:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00424f83:
        mov eax,dword ptr [ebx+45Ch]
    L_00424f89:
        mov dword ptr [data_00491bf0],eax
    L_00424f8e:
        jmp short L_00424fe3
    L_00424f90:
        mov esi,dword ptr [data_00491c10]
    L_00424f96:
        mov edi,dword ptr [esi+3AD08Ch]
    L_00424f9c:
        add esi,3AD08Ch
    L_00424fa2:
        test edi,edi
    L_00424fa4:
        je short L_00424fbc
    L_00424fa6:
        call asm_FUN_00447810_00447810
    L_00424fab:
        mov ecx,dword ptr [esi]
    L_00424fad:
        push ecx
    L_00424fae:
        call asm_free_004524a1
    L_00424fb3:
        add esp,4
    L_00424fb6:
        mov dword ptr [esi],0
    L_00424fbc:
        mov eax,dword ptr [ebx+45Ch]
    L_00424fc2:
        test eax,eax
    L_00424fc4:
        je short L_00424fd9
    L_00424fc6:
        push eax
    L_00424fc7:
        call asm_free_00452422
    L_00424fcc:
        add esp,4
    L_00424fcf:
        mov dword ptr [ebx+45Ch],0
    L_00424fd9:
        mov dword ptr [data_00491bf0],0
    L_00424fe3:
        mov eax,dword ptr [ebx+36Ch]
    L_00424fe9:
        test eax,eax
    L_00424feb:
        je short L_00424ff6
    L_00424fed:
        push eax
    L_00424fee:
        call asm_free_00452422
    L_00424ff3:
        add esp,4
    L_00424ff6:
        mov ecx,dword ptr [esp+10h]
    L_00424ffa:
        pop edi
    L_00424ffb:
        pop esi
    L_00424ffc:
        mov dword ptr [ebx+36Ch],0
    L_00425006:
        pop ebp
    L_00425007:
        mov dword ptr fs:[0],ecx
    L_0042500e:
        pop ebx
    L_0042500f:
        add esp,0Ch
    L_00425012:
        ret 4
    }
}

// 0x004294A0..0x0042960E: FUN_004294a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004294a0_004294a0() {
    __asm {
    L_004294a0:
        push 0FFFFFFFFh
    L_004294a2:
        push 465268h
    L_004294a7:
        mov eax,dword ptr fs:[0]
    L_004294ad:
        push eax
    L_004294ae:
        mov dword ptr fs:[0],esp
    L_004294b5:
        push ecx
    L_004294b6:
        push ebx
    L_004294b7:
        push ebp
    L_004294b8:
        push esi
    L_004294b9:
        push edi
    L_004294ba:
        mov edi,dword ptr [esp+24h]
    L_004294be:
        xor ebp,ebp
    L_004294c0:
        mov dword ptr [esp+1Ch],ebp
    L_004294c4:
        mov eax,dword ptr [edi+14h]
    L_004294c7:
        push eax
    L_004294c8:
        call asm_free_004524a1
    L_004294cd:
        add esp,4
    L_004294d0:
        xor esi,esi
    L_004294d2:
        mov eax,esi
    L_004294d4:
        mov ecx,edi
    L_004294d6:
        call asm_FUN_0042ab20_0042ab20
    L_004294db:
        inc esi
    L_004294dc:
        cmp esi,8
    L_004294df:
        jl short L_004294d2
    L_004294e1:
        mov eax,dword ptr [edi+18h]
    L_004294e4:
        push eax
    L_004294e5:
        call asm_free_004524a1
    L_004294ea:
        add esp,4
    L_004294ed:
        mov dword ptr [edi+18h],ebp
    L_004294f0:
        lea esi,[edi+1Ch]
    L_004294f3:
        mov ebx,8
    L_004294f8:
        mov eax,dword ptr [esi]
    L_004294fa:
        push eax
    L_004294fb:
        call asm_free_004524a1
    L_00429500:
        mov dword ptr [esi],ebp
    L_00429502:
        add esp,4
    L_00429505:
        add esi,4
    L_00429508:
        dec ebx
    L_00429509:
        jne short L_004294f8
    L_0042950b:
        mov esi,dword ptr [edi+8]
    L_0042950e:
        mov ebx,dword ptr [data_004660b0]
    L_00429514:
        cmp esi,ebp
    L_00429516:
        mov ebp,dword ptr [data_004660b4]
    L_0042951c:
        je short L_0042954c
    L_0042951e:
        mov eax,dword ptr [data_00491be4]
    L_00429523:
        push 492274h
    L_00429528:
        mov dword ptr [esp+14h],eax
    L_0042952c:
        call ebx
    L_0042952e:
        inc byte ptr [data_0049231c]
    L_00429534:
        mov edx,dword ptr [esp+10h]
    L_00429538:
        mov ecx,esi
    L_0042953a:
        call asm_Scheduler_Remove_00449f60
    L_0042953f:
        push 492274h
    L_00429544:
        call ebp
    L_00429546:
        dec byte ptr [data_0049231c]
    L_0042954c:
        mov eax,dword ptr [edi+1CCh]
    L_00429552:
        test eax,eax
    L_00429554:
        mov dword ptr [esp+10h],eax
    L_00429558:
        je short L_0042958d
    L_0042955a:
        mov esi,dword ptr [data_00491be4]
    L_00429560:
        push 492274h
    L_00429565:
        call ebx
    L_00429567:
        mov dl,byte ptr [data_0049231c]
    L_0042956d:
        mov ecx,dword ptr [esp+10h]
    L_00429571:
        inc dl
    L_00429573:
        mov byte ptr [data_0049231c],dl
    L_00429579:
        mov edx,esi
    L_0042957b:
        call asm_Scheduler_Remove_00449f60
    L_00429580:
        push 492274h
    L_00429585:
        call ebp
    L_00429587:
        dec byte ptr [data_0049231c]
    L_0042958d:
        mov eax,dword ptr [edi+0Ch]
    L_00429590:
        test eax,eax
    L_00429592:
        mov dword ptr [esp+10h],eax
    L_00429596:
        je short L_004295cb
    L_00429598:
        mov esi,dword ptr [data_00491be4]
    L_0042959e:
        push 492274h
    L_004295a3:
        call ebx
    L_004295a5:
        mov dl,byte ptr [data_0049231c]
    L_004295ab:
        mov ecx,dword ptr [esp+10h]
    L_004295af:
        inc dl
    L_004295b1:
        mov byte ptr [data_0049231c],dl
    L_004295b7:
        mov edx,esi
    L_004295b9:
        call asm_Scheduler_Remove_00449f60
    L_004295be:
        push 492274h
    L_004295c3:
        call ebp
    L_004295c5:
        dec byte ptr [data_0049231c]
    L_004295cb:
        cmp edi,dword ptr [data_00477838]
    L_004295d1:
        jne short L_004295dd
    L_004295d3:
        mov dword ptr [data_00477838],0
    L_004295dd:
        push 42AC60h
    L_004295e2:
        push 8
    L_004295e4:
        push 24h
    L_004295e6:
        add edi,0A0h
    L_004295ec:
        push edi
    L_004295ed:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_004295f5:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004295fa:
        mov ecx,dword ptr [esp+14h]
    L_004295fe:
        pop edi
    L_004295ff:
        pop esi
    L_00429600:
        pop ebp
    L_00429601:
        pop ebx
    L_00429602:
        mov dword ptr fs:[0],ecx
    L_00429609:
        add esp,10h
    L_0042960c:
        ret 4
    }
}

// 0x0042CB60..0x0042CD4A: FUN_0042cb60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042cb60_0042cb60() {
    __asm {
    L_0042cb60:
        push 0FFFFFFFFh
    L_0042cb62:
        push 46562Eh
    L_0042cb67:
        mov eax,dword ptr fs:[0]
    L_0042cb6d:
        push eax
    L_0042cb6e:
        mov dword ptr fs:[0],esp
    L_0042cb75:
        push ecx
    L_0042cb76:
        push ebx
    L_0042cb77:
        push ebp
    L_0042cb78:
        push esi
    L_0042cb79:
        push edi
    L_0042cb7a:
        mov edi,dword ptr [esp+24h]
    L_0042cb7e:
        mov dword ptr [edi],46ECF0h
    L_0042cb84:
        lea esi,[edi+5AB0h]
    L_0042cb8a:
        mov dword ptr [esp+1Ch],0
    L_0042cb92:
        mov dword ptr [esp+10h],esi
    L_0042cb96:
        call asm_Platform_StopWorker_0044c150
    L_0042cb9b:
        mov edi,dword ptr [edi+0Ch]
    L_0042cb9e:
        test edi,edi
    L_0042cba0:
        mov ebx,dword ptr [data_00491be4]
    L_0042cba6:
        mov esi,dword ptr [data_004660b0]
    L_0042cbac:
        mov ebp,dword ptr [data_004660b4]
    L_0042cbb2:
        je short L_0042cbd7
    L_0042cbb4:
        push 492274h
    L_0042cbb9:
        call esi
    L_0042cbbb:
        inc byte ptr [data_0049231c]
    L_0042cbc1:
        mov ecx,edi
    L_0042cbc3:
        mov edx,ebx
    L_0042cbc5:
        call asm_Scheduler_Remove_00449f60
    L_0042cbca:
        push 492274h
    L_0042cbcf:
        call ebp
    L_0042cbd1:
        dec byte ptr [data_0049231c]
    L_0042cbd7:
        mov eax,dword ptr [esp+24h]
    L_0042cbdb:
        mov edi,dword ptr [eax+10h]
    L_0042cbde:
        test edi,edi
    L_0042cbe0:
        mov ebx,dword ptr [data_00491be4]
    L_0042cbe6:
        je short L_0042cc0b
    L_0042cbe8:
        push 492274h
    L_0042cbed:
        call esi
    L_0042cbef:
        inc byte ptr [data_0049231c]
    L_0042cbf5:
        mov ecx,edi
    L_0042cbf7:
        mov edx,ebx
    L_0042cbf9:
        call asm_Scheduler_Remove_00449f60
    L_0042cbfe:
        push 492274h
    L_0042cc03:
        call ebp
    L_0042cc05:
        dec byte ptr [data_0049231c]
    L_0042cc0b:
        mov ebx,dword ptr [data_00491c10]
    L_0042cc11:
        mov edi,dword ptr [ebx+3AD0D0h]
    L_0042cc17:
        add ebx,3AD0D0h
    L_0042cc1d:
        xor ebp,ebp
    L_0042cc1f:
        cmp edi,ebp
    L_0042cc21:
        je short L_0042cc35
    L_0042cc23:
        call asm_FUN_00447810_00447810
    L_0042cc28:
        mov ecx,dword ptr [ebx]
    L_0042cc2a:
        push ecx
    L_0042cc2b:
        call asm_free_004524a1
    L_0042cc30:
        add esp,4
    L_0042cc33:
        mov dword ptr [ebx],ebp
    L_0042cc35:
        mov ebx,dword ptr [data_00491c10]
    L_0042cc3b:
        mov edi,dword ptr [ebx+3AD0D4h]
    L_0042cc41:
        add ebx,3AD0D4h
    L_0042cc47:
        cmp edi,ebp
    L_0042cc49:
        je short L_0042cc5d
    L_0042cc4b:
        call asm_FUN_00447810_00447810
    L_0042cc50:
        mov edx,dword ptr [ebx]
    L_0042cc52:
        push edx
    L_0042cc53:
        call asm_free_004524a1
    L_0042cc58:
        add esp,4
    L_0042cc5b:
        mov dword ptr [ebx],ebp
    L_0042cc5d:
        mov ebx,dword ptr [esp+24h]
    L_0042cc61:
        add ebx,59E4h
    L_0042cc67:
        mov esi,32h
    L_0042cc6c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0042cc70:
        mov edi,dword ptr [ebx]
    L_0042cc72:
        cmp edi,ebp
    L_0042cc74:
        je short L_0042cc85
    L_0042cc76:
        push edi
    L_0042cc77:
        call asm_FUN_004294a0_004294a0
    L_0042cc7c:
        push edi
    L_0042cc7d:
        call asm_free_004524a1
    L_0042cc82:
        add esp,4
    L_0042cc85:
        add ebx,4
    L_0042cc88:
        dec esi
    L_0042cc89:
        jne short L_0042cc70
    L_0042cc8b:
        mov esi,dword ptr [esp+24h]
    L_0042cc8f:
        mov ecx,dword ptr [esi+5D0h]
    L_0042cc95:
        cmp ecx,ebp
    L_0042cc97:
        je short L_0042cd04
    L_0042cc99:
        mov edx,dword ptr [data_00491c10]
    L_0042cc9f:
        mov eax,dword ptr [edx+72DAD4h]
    L_0042cca5:
        cmp eax,ebp
    L_0042cca7:
        je short L_0042ccbd
    L_0042cca9:
        lea esp,[esp+force_disp32_zero]
    L_0042ccb0:
        mov edi,dword ptr [eax]
    L_0042ccb2:
        cmp dword ptr [edi],ecx
    L_0042ccb4:
        je short L_0042ccd6
    L_0042ccb6:
        mov eax,dword ptr [eax+4]
    L_0042ccb9:
        cmp eax,ebp
    L_0042ccbb:
        jne short L_0042ccb0
    L_0042ccbd:
        mov eax,dword ptr [edx+72DADCh]
    L_0042ccc3:
        cmp eax,ebp
    L_0042ccc5:
        je short L_0042cd04
    L_0042ccc7:
        mov edx,dword ptr [eax]
    L_0042ccc9:
        cmp dword ptr [edx],ecx
    L_0042cccb:
        je short L_0042ccd6
    L_0042cccd:
        mov eax,dword ptr [eax+4]
    L_0042ccd0:
        cmp eax,ebp
    L_0042ccd2:
        jne short L_0042ccc7
    L_0042ccd4:
        jmp short L_0042cd04
    L_0042ccd6:
        mov eax,dword ptr [eax]
    L_0042ccd8:
        cmp eax,ebp
    L_0042ccda:
        je short L_0042cd04
    L_0042ccdc:
        cmp dword ptr [eax+18h],ebp
    L_0042ccdf:
        mov ecx,1
    L_0042cce4:
        mov word ptr [eax+304h],cx
    L_0042cceb:
        jne short L_0042cd04
    L_0042cced:
        mov eax,dword ptr [eax+14h]
    L_0042ccf0:
        cmp eax,ebp
    L_0042ccf2:
        je short L_0042cd04
    L_0042ccf4:
        mov edx,dword ptr [eax]
    L_0042ccf6:
        mov word ptr [edx+304h],cx
    L_0042ccfd:
        mov eax,dword ptr [eax+4]
    L_0042cd00:
        cmp eax,ebp
    L_0042cd02:
        jne short L_0042ccf4
    L_0042cd04:
        mov eax,dword ptr [esi+5AACh]
    L_0042cd0a:
        cmp eax,ebp
    L_0042cd0c:
        je short L_0042cd21
    L_0042cd0e:
        push eax
    L_0042cd0f:
        call asm_free_00452422
    L_0042cd14:
        mov eax,dword ptr [esp+28h]
    L_0042cd18:
        add esp,4
    L_0042cd1b:
        mov dword ptr [eax+5AACh],ebp
    L_0042cd21:
        mov esi,dword ptr [esp+10h]
    L_0042cd25:
        mov dword ptr [data_0047784c],ebp
    L_0042cd2b:
        mov dword ptr [esi],4703E4h
    L_0042cd31:
        call asm_Platform_StopWorker_0044c150
    L_0042cd36:
        mov ecx,dword ptr [esp+14h]
    L_0042cd3a:
        pop edi
    L_0042cd3b:
        pop esi
    L_0042cd3c:
        pop ebp
    L_0042cd3d:
        pop ebx
    L_0042cd3e:
        mov dword ptr fs:[0],ecx
    L_0042cd45:
        add esp,10h
    L_0042cd48:
        ret 4
    }
}
