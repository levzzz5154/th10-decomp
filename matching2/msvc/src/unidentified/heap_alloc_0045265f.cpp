#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045265F..0x004526CD: __heap_alloc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_heap_alloc_0045265f() {
    __asm {
    L_0045265f:
        push 0Ch
    L_00452661:
        push 46A6D0h
    L_00452666:
        call asm_SEH_prolog_00454bbc
    L_0045266b:
        mov esi,dword ptr [ebp+8]
    L_0045266e:
        cmp dword ptr [data_00499344],3
    L_00452675:
        jne short L_004526a5
    L_00452677:
        cmp esi,dword ptr [data_00499330]
    L_0045267d:
        ja short L_004526a5
    L_0045267f:
        push 4
    L_00452681:
        call asm_lock_00453c0c
    L_00452686:
        pop ecx
    L_00452687:
        and dword ptr [ebp-4],0
    L_0045268b:
        push esi
    L_0045268c:
        call asm_sbh_alloc_block_004548be
    L_00452691:
        pop ecx
    L_00452692:
        mov dword ptr [ebp-1Ch],eax
    L_00452695:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00452699:
        call asm_FUN_004526d1_004526d1
    L_0045269e:
        mov eax,dword ptr [ebp-1Ch]
    L_004526a1:
        test eax,eax
    L_004526a3:
        jne short L_004526c8
    L_004526a5:
        test esi,esi
    L_004526a7:
        jne short L_004526aa
    L_004526a9:
        inc esi
    L_004526aa:
        cmp dword ptr [data_00499344],1
    L_004526b1:
        je short L_004526b9
    L_004526b3:
        add esi,0Fh
    L_004526b6:
        and esi,0FFFFFFF0h
    L_004526b9:
        push esi
    L_004526ba:
        push 0
    L_004526bc:
        push dword ptr [data_00499340]
    L_004526c2:
        call dword ptr [data_004661e4]
    L_004526c8:
        call asm_SEH_epilog_00454bf7
    L_004526cd:
        ret
    }
}
