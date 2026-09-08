#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F7D7..0x0045FA19: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f7d7() {
    __asm {
    L_0045f7d7:
        push 14h
    L_0045f7d9:
        push 46C8A0h
    L_0045f7de:
        call asm_SEH_prolog_00454bbc
    L_0045f7e3:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_0045f7e7:
        push 0Bh
    L_0045f7e9:
        call asm_mtinitlocknum_00453b6c
    L_0045f7ee:
        pop ecx
    L_0045f7ef:
        test eax,eax
    L_0045f7f1:
        je asm_target_0045f878
    L_0045f7f7:
        push 0Bh
    L_0045f7f9:
        call asm_lock_00453c0c
    L_0045f7fe:
        pop ecx
    L_0045f7ff:
        xor edi,edi
    L_0045f801:
        mov dword ptr [ebp-4],edi
    L_0045f804:
        mov dword ptr [ebp-24h],edi
    L_0045f807:
        cmp edi,40h
    L_0045f80a:
        jge asm_target_0045f938
    L_0045f810:
        mov esi,dword ptr [edi*4+499200h]
    L_0045f817:
        test esi,esi
    L_0045f819:
        je asm_target_0045f8e1
    L_0045f81f:
        mov dword ptr [ebp-20h],esi
    L_0045f822:
        mov eax,dword ptr [edi*4+499200h]
    L_0045f829:
        add eax,480h
    L_0045f82e:
        cmp esi,eax
    L_0045f830:
        jae asm_target_0045f8d5
    L_0045f836:
        test byte ptr [esi+4],1
    L_0045f83a:
        jne short L_0045f8a2
    L_0045f83c:
        xor ebx,ebx
    L_0045f83e:
        cmp dword ptr [esi+8],ebx
    L_0045f841:
        jne short L_0045f88b
    L_0045f843:
        push 0Ah
    L_0045f845:
        call asm_lock_00453c0c
    L_0045f84a:
        pop ecx
    L_0045f84b:
        mov dword ptr [ebp-4],1
    L_0045f852:
        cmp dword ptr [esi+8],ebx
    L_0045f855:
        jne short L_0045f883
    L_0045f857:
        push 0FA0h
    L_0045f85c:
        lea eax,[esi+0Ch]
    L_0045f85f:
        push eax
    L_0045f860:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_0045f865:
        pop ecx
    L_0045f866:
        pop ecx
    L_0045f867:
        test eax,eax
    L_0045f869:
        jne short L_0045f880
    L_0045f86b:
        push 0FFFFFFFFh
    L_0045f86d:
        lea eax,[ebp-10h]
    L_0045f870:
        push eax
    L_0045f871:
        call asm_local_unwind2_004598de
    L_0045f876:
        pop ecx
    L_0045f877:
        pop ecx
    L_0045f878:
        or eax,0FFFFFFFFh
    L_0045f87b:
        jmp asm_target_0045f944
    L_0045f880:
        inc dword ptr [esi+8]
    L_0045f883:
        mov dword ptr [ebp-4],ebx
    L_0045f886:
        call asm_target_0045f8b0
    L_0045f88b:
        lea ebx,[esi+0Ch]
    L_0045f88e:
        push ebx
    L_0045f88f:
        call dword ptr [data_004660b0]
    L_0045f895:
        test byte ptr [esi+4],1
    L_0045f899:
        je short L_0045f8b9
    L_0045f89b:
        push ebx
    L_0045f89c:
        call dword ptr [data_004660b4]
    L_0045f8a2:
        add esi,24h
    L_0045f8a5:
        jmp asm_target_0045f81f
    L_0045f8aa:
        mov edi,dword ptr [ebp-24h]
    L_0045f8ad:
        mov esi,dword ptr [ebp-20h]
    L_0045f8b0:
        push 0Ah
    L_0045f8b2:
        call asm_FUN_00453b3f_00453b3f
    L_0045f8b7:
        pop ecx
    L_0045f8b8:
        ret
    L_0045f8b9:
        or dword ptr [esi],0FFFFFFFFh
    L_0045f8bc:
        mov eax,esi
    L_0045f8be:
        sub eax,dword ptr [edi*4+499200h]
    L_0045f8c5:
        cdq
    L_0045f8c6:
        push 24h
    L_0045f8c8:
        pop ecx
    L_0045f8c9:
        idiv ecx
    L_0045f8cb:
        mov ecx,edi
    L_0045f8cd:
        shl ecx,5
    L_0045f8d0:
        add eax,ecx
    L_0045f8d2:
        mov dword ptr [ebp-1Ch],eax
    L_0045f8d5:
        cmp dword ptr [ebp-1Ch],0FFFFFFFFh
    L_0045f8d9:
        jne short L_0045f938
    L_0045f8db:
        inc edi
    L_0045f8dc:
        jmp asm_target_0045f804
    L_0045f8e1:
        mov esi,480h
    L_0045f8e6:
        push esi
    L_0045f8e7:
        call asm_malloc_00452706
    L_0045f8ec:
        pop ecx
    L_0045f8ed:
        mov dword ptr [ebp-20h],eax
    L_0045f8f0:
        test eax,eax
    L_0045f8f2:
        je short L_0045f938
    L_0045f8f4:
        lea ecx,[edi*4+499200h]
    L_0045f8fb:
        mov dword ptr [ecx],eax
    L_0045f8fd:
        add dword ptr [data_004991e4],20h
    L_0045f904:
        mov edx,dword ptr [ecx]
    L_0045f906:
        add edx,esi
    L_0045f908:
        cmp eax,edx
    L_0045f90a:
        jae short L_0045f923
    L_0045f90c:
        mov byte ptr [eax+4],0
    L_0045f910:
        or dword ptr [eax],0FFFFFFFFh
    L_0045f913:
        mov byte ptr [eax+5],0Ah
    L_0045f917:
        and dword ptr [eax+8],0
    L_0045f91b:
        add eax,24h
    L_0045f91e:
        mov dword ptr [ebp-20h],eax
    L_0045f921:
        jmp short L_0045f904
    L_0045f923:
        shl edi,5
    L_0045f926:
        mov dword ptr [ebp-1Ch],edi
    L_0045f929:
        push edi
    L_0045f92a:
        call asm_lock_fhandle_0045f715
    L_0045f92f:
        pop ecx
    L_0045f930:
        test eax,eax
    L_0045f932:
        jne short L_0045f938
    L_0045f934:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_0045f938:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045f93c:
        call asm_target_0045f94a
    L_0045f941:
        mov eax,dword ptr [ebp-1Ch]
    L_0045f944:
        call asm_SEH_epilog_00454bf7
    L_0045f949:
        ret
    L_0045f94a:
        push 0Bh
    L_0045f94c:
        call asm_FUN_00453b3f_00453b3f
    L_0045f951:
        pop ecx
    L_0045f952:
        ret
    L_0045f953:
        push 10h
    L_0045f955:
        push 46C8B8h
    L_0045f95a:
        call asm_SEH_prolog_00454bbc
    L_0045f95f:
        xor bl,bl
    L_0045f961:
        test byte ptr [ebp+0Ch],8
    L_0045f965:
        je short L_0045f96a
    L_0045f967:
        add bl,20h
    L_0045f96a:
        test byte ptr [ebp+0Dh],40h
    L_0045f96e:
        je short L_0045f973
    L_0045f970:
        or bl,80h
    L_0045f973:
        test byte ptr [ebp+0Ch],80h
    L_0045f977:
        je short L_0045f97c
    L_0045f979:
        or bl,10h
    L_0045f97c:
        push dword ptr [ebp+8]
    L_0045f97f:
        call dword ptr [data_00466080]
    L_0045f985:
        test eax,eax
    L_0045f987:
        jne short L_0045f998
    L_0045f989:
        call dword ptr [data_0046610c]
    L_0045f98f:
        push eax
    L_0045f990:
        call asm_dosmaperr_00456b04
    L_0045f995:
        pop ecx
    L_0045f996:
        jmp short L_0045f9cc
    L_0045f998:
        cmp eax,2
    L_0045f99b:
        jne short L_0045f9a2
    L_0045f99d:
        or bl,40h
    L_0045f9a0:
        jmp short L_0045f9aa
    L_0045f9a2:
        cmp eax,3
    L_0045f9a5:
        jne short L_0045f9aa
    L_0045f9a7:
        or bl,8
    L_0045f9aa:
        call asm_unassigned_0045f7d7
    L_0045f9af:
        mov esi,eax
    L_0045f9b1:
        mov dword ptr [ebp-20h],esi
    L_0045f9b4:
        cmp esi,0FFFFFFFFh
    L_0045f9b7:
        jne short L_0045f9d1
    L_0045f9b9:
        call asm_FUN_00456af2_00456af2
    L_0045f9be:
        mov dword ptr [eax],18h
    L_0045f9c4:
        call asm_FUN_00456afb_00456afb
    L_0045f9c9:
        and dword ptr [eax],0
    L_0045f9cc:
        or eax,0FFFFFFFFh
    L_0045f9cf:
        jmp short L_0045fa09
    L_0045f9d1:
        and dword ptr [ebp-4],0
    L_0045f9d5:
        push dword ptr [ebp+8]
    L_0045f9d8:
        push esi
    L_0045f9d9:
        call asm_target_0045f5d9
    L_0045f9de:
        pop ecx
    L_0045f9df:
        pop ecx
    L_0045f9e0:
        or bl,1
    L_0045f9e3:
        mov byte ptr [ebp-19h],bl
    L_0045f9e6:
        mov ecx,esi
    L_0045f9e8:
        sar ecx,5
    L_0045f9eb:
        mov eax,esi
    L_0045f9ed:
        and eax,1Fh
    L_0045f9f0:
        lea eax,[eax+eax*8]
    L_0045f9f3:
        mov ecx,dword ptr [ecx*4+499200h]
    L_0045f9fa:
        mov byte ptr [ecx+eax*4+4],bl
    L_0045f9fe:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fa02:
        call asm_target_0045fa12
    L_0045fa07:
        mov eax,esi
    L_0045fa09:
        call asm_SEH_epilog_00454bf7
    L_0045fa0e:
        ret
    L_0045fa0f:
        mov esi,dword ptr [ebp-20h]
    L_0045fa12:
        push esi
    L_0045fa13:
        call asm_FUN_0045f7b5_0045f7b5
    L_0045fa18:
        pop ecx
    L_0045fa19:
        ret
    }
}
