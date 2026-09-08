#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045794D..0x00457A0F: FUN_0045794d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045794d_0045794d() {
    __asm {
    L_0045794d:
        push 10h
    L_0045794f:
        push 46AB38h
    L_00457954:
        call asm_SEH_prolog_00454bbc
    L_00457959:
        mov ecx,dword ptr [ebp+8]
    L_0045795c:
        test ecx,ecx
    L_0045795e:
        jbe short L_00457973
    L_00457960:
        push 0FFFFFFE0h
    L_00457962:
        pop eax
    L_00457963:
        xor edx,edx
    L_00457965:
        div ecx
    L_00457967:
        cmp eax,dword ptr [ebp+0Ch]
    L_0045796a:
        jae short L_00457973
    L_0045796c:
        xor eax,eax
    L_0045796e:
        jmp asm_target_00457a1e
    L_00457973:
        imul ecx,dword ptr [ebp+0Ch]
    L_00457977:
        mov esi,ecx
    L_00457979:
        mov dword ptr [ebp-20h],esi
    L_0045797c:
        test esi,esi
    L_0045797e:
        jne short L_00457981
    L_00457980:
        inc esi
    L_00457981:
        xor edi,edi
    L_00457983:
        mov dword ptr [ebp-1Ch],edi
    L_00457986:
        cmp esi,0FFFFFFE0h
    L_00457989:
        ja short L_004579f0
    L_0045798b:
        cmp dword ptr [data_00499344],3
    L_00457992:
        jne short L_004579db
    L_00457994:
        add esi,0Fh
    L_00457997:
        and esi,0FFFFFFF0h
    L_0045799a:
        mov dword ptr [ebp+0Ch],esi
    L_0045799d:
        mov ebx,dword ptr [ebp-20h]
    L_004579a0:
        cmp ebx,dword ptr [data_00499330]
    L_004579a6:
        ja short L_004579db
    L_004579a8:
        push 4
    L_004579aa:
        call asm_lock_00453c0c
    L_004579af:
        pop ecx
    L_004579b0:
        and dword ptr [ebp-4],edi
    L_004579b3:
        push ebx
    L_004579b4:
        call asm_sbh_alloc_block_004548be
    L_004579b9:
        pop ecx
    L_004579ba:
        mov dword ptr [ebp-1Ch],eax
    L_004579bd:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004579c1:
        call asm_FUN_00457a13_00457a13
    L_004579c6:
        mov edi,dword ptr [ebp-1Ch]
    L_004579c9:
        test edi,edi
    L_004579cb:
        je short L_004579df
    L_004579cd:
        push dword ptr [ebp-20h]
    L_004579d0:
        push 0
    L_004579d2:
        push edi
    L_004579d3:
        call asm_memset_0045bed0
    L_004579d8:
        add esp,0Ch
    L_004579db:
        test edi,edi
    L_004579dd:
        TH10_REL8(0x75, 0x004579dd, VA_asm_FUN_0045794d_part_00457a1c)
    L_004579df:
        push esi
    L_004579e0:
        push 8
    L_004579e2:
        push dword ptr [data_00499340]
    L_004579e8:
        call dword ptr [data_004661e4]
    L_004579ee:
        mov edi,eax
    L_004579f0:
        test edi,edi
    L_004579f2:
        TH10_REL8(0x75, 0x004579f2, VA_asm_FUN_0045794d_part_00457a1c)
    L_004579f4:
        cmp dword ptr [data_00477364],edi
    L_004579fa:
        TH10_REL8(0x74, 0x004579fa, VA_asm_FUN_0045794d_part_00457a1c)
    L_004579fc:
        push esi
    L_004579fd:
        call asm_callnewh_00455737
    L_00457a02:
        pop ecx
    L_00457a03:
        test eax,eax
    L_00457a05:
        jne asm_target_00457981
    L_00457a0b:
        jmp asm_target_0045796c
    }
}

// 0x00457A1C..0x00457A23: FUN_0045794d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045794d_part_00457a1c() {
    __asm {
    L_00457a1c:
        mov eax,edi
    L_00457a1e:
        call asm_SEH_epilog_00454bf7
    L_00457a23:
        ret
    }
}
