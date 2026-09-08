#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045772C..0x00457795: __msize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_msize_0045772c() {
    __asm {
    L_0045772c:
        push 10h
    L_0045772e:
        push 46AB28h
    L_00457733:
        call asm_SEH_prolog_00454bbc
    L_00457738:
        cmp dword ptr [data_00499344],3
    L_0045773f:
        jne short L_0045777b
    L_00457741:
        push 4
    L_00457743:
        call asm_lock_00453c0c
    L_00457748:
        pop ecx
    L_00457749:
        and dword ptr [ebp-4],0
    L_0045774d:
        mov esi,dword ptr [ebp+8]
    L_00457750:
        push esi
    L_00457751:
        call asm_sbh_find_block_00453c9a
    L_00457756:
        pop ecx
    L_00457757:
        mov dword ptr [ebp-20h],eax
    L_0045775a:
        test eax,eax
    L_0045775c:
        je short L_00457769
    L_0045775e:
        mov esi,dword ptr [esi-4]
    L_00457761:
        sub esi,9
    L_00457764:
        mov dword ptr [ebp-1Ch],esi
    L_00457767:
        jmp short L_0045776c
    L_00457769:
        mov esi,dword ptr [ebp-1Ch]
    L_0045776c:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00457770:
        call asm_FUN_00457799_00457799
    L_00457775:
        cmp dword ptr [ebp-20h],0
    L_00457779:
        jne short L_0045778e
    L_0045777b:
        push dword ptr [ebp+8]
    L_0045777e:
        push 0
    L_00457780:
        push dword ptr [data_00499340]
    L_00457786:
        call dword ptr [data_00466140]
    L_0045778c:
        mov esi,eax
    L_0045778e:
        mov eax,esi
    L_00457790:
        call asm_SEH_epilog_00454bf7
    L_00457795:
        ret
    }
}
