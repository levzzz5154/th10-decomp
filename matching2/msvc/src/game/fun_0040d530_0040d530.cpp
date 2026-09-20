// BLOCKED (H2501): closest_byte_count=300/300; first_diff=0x0040D55E
// (+0x2E), with the mirrored site at 0x0040D592 (+0x62);
// residual_class=MSVC c2 register-register argument-copy order (retail copies
// ECX before EDX, while both available toolkit revisions copy EDX before ECX);
// variants_tested=56 call-setup shapes plus the earlier matrix, both cl 13.10
// revisions, plain /O2 and native /GL+/LTCG, home permutations, caller/callee
// visibility, and register-pressure ballast;
// next_lever=use a compiler/toolkit whose two-register copies schedule in
// ascending parameter-home order, then rerun the merged EnemyManager/Scheduler
// cluster; retain this exact wrapper until that ABI lever exists.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

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
