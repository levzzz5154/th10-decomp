#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045252D..0x00452576: `eh_vector_constructor_iterator'
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_eh_vector_constructor_iterator_0045252d() {
    __asm {
    L_0045252d:
        push 10h
    L_0045252f:
        push 46A6A0h
    L_00452534:
        call asm_SEH_prolog_00454bbc
    L_00452539:
        xor eax,eax
    L_0045253b:
        mov dword ptr [ebp-20h],eax
    L_0045253e:
        mov dword ptr [ebp-4],eax
    L_00452541:
        mov dword ptr [ebp-1Ch],eax
    L_00452544:
        mov eax,dword ptr [ebp-1Ch]
    L_00452547:
        cmp eax,dword ptr [ebp+10h]
    L_0045254a:
        jge short L_0045255f
    L_0045254c:
        mov esi,dword ptr [ebp+8]
    L_0045254f:
        mov ecx,esi
    L_00452551:
        call dword ptr [ebp+14h]
    L_00452554:
        add esi,dword ptr [ebp+0Ch]
    L_00452557:
        mov dword ptr [ebp+8],esi
    L_0045255a:
        inc dword ptr [ebp-1Ch]
    L_0045255d:
        jmp short L_00452544
    L_0045255f:
        mov dword ptr [ebp-20h],1
    L_00452566:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045256a:
        call asm_FUN_00452577_00452577
    L_0045256f:
        call asm_SEH_epilog_00454bf7
    L_00452574:
        ret 14h
    }
}
