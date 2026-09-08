#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004614A9..0x00461545: __commit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_commit_004614a9() {
    __asm {
    L_004614a9:
        push 0Ch
    L_004614ab:
        push 46C970h
    L_004614b0:
        call asm_SEH_prolog_00454bbc
    L_004614b5:
        mov ebx,dword ptr [ebp+8]
    L_004614b8:
        cmp ebx,dword ptr [data_004991e4]
    L_004614be:
        jae asm_commit_part_00461551
    L_004614c4:
        mov eax,ebx
    L_004614c6:
        sar eax,5
    L_004614c9:
        lea edi,[eax*4+499200h]
    L_004614d0:
        mov eax,ebx
    L_004614d2:
        and eax,1Fh
    L_004614d5:
        lea esi,[eax+eax*8]
    L_004614d8:
        shl esi,2
    L_004614db:
        mov eax,dword ptr [edi]
    L_004614dd:
        test byte ptr [eax+esi+4],1
    L_004614e2:
        TH10_REL8(0x74, 0x004614e2, VA_asm_commit_part_00461551)
    L_004614e4:
        push ebx
    L_004614e5:
        call asm_lock_fhandle_0045f715
    L_004614ea:
        pop ecx
    L_004614eb:
        and dword ptr [ebp-4],0
    L_004614ef:
        mov eax,dword ptr [edi]
    L_004614f1:
        test byte ptr [eax+esi+4],1
    L_004614f6:
        je short L_00461529
    L_004614f8:
        push ebx
    L_004614f9:
        call asm_get_osfhandle_0045f6d4
    L_004614fe:
        pop ecx
    L_004614ff:
        push eax
    L_00461500:
        call dword ptr [data_004661c4]
    L_00461506:
        test eax,eax
    L_00461508:
        jne short L_00461515
    L_0046150a:
        call dword ptr [data_0046610c]
    L_00461510:
        mov dword ptr [ebp-1Ch],eax
    L_00461513:
        jmp short L_00461519
    L_00461515:
        and dword ptr [ebp-1Ch],0
    L_00461519:
        cmp dword ptr [ebp-1Ch],0
    L_0046151d:
        je short L_00461538
    L_0046151f:
        call asm_FUN_00456afb_00456afb
    L_00461524:
        mov ecx,dword ptr [ebp-1Ch]
    L_00461527:
        mov dword ptr [eax],ecx
    L_00461529:
        call asm_FUN_00456af2_00456af2
    L_0046152e:
        mov dword ptr [eax],9
    L_00461534:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_00461538:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0046153c:
        call asm_FUN_00461549_00461549
    L_00461541:
        mov eax,dword ptr [ebp-1Ch]
    L_00461544:
        TH10_REL8(0xeb, 0x00461544, VA_asm_target_0046155f)
    }
}

// 0x00461551..0x00461564: __commit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_commit_part_00461551() {
    __asm {
    L_00461551:
        call asm_FUN_00456af2_00456af2
    L_00461556:
        mov dword ptr [eax],9
    L_0046155c:
        or eax,0FFFFFFFFh
    L_0046155f:
        call asm_SEH_epilog_00454bf7
    L_00461564:
        ret
    }
}
