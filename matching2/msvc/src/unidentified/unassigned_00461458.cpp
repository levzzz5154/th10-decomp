#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461458..0x004614A8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461458() {
    __asm {
    L_00461458:
        push 0Ch
    L_0046145a:
        push 46C960h
    L_0046145f:
        call asm_SEH_prolog_00454bbc
    L_00461464:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_00461468:
        mov esi,dword ptr [ebp+8]
    L_0046146b:
        test byte ptr [esi+0Ch],40h
    L_0046146f:
        je short L_0046147e
    L_00461471:
        and dword ptr [esi+0Ch],0
    L_00461475:
        mov eax,dword ptr [ebp-1Ch]
    L_00461478:
        call asm_SEH_epilog_00454bf7
    L_0046147d:
        ret
    L_0046147e:
        push esi
    L_0046147f:
        call asm_target_0045a06a
    L_00461484:
        pop ecx
    L_00461485:
        and dword ptr [ebp-4],0
    L_00461489:
        push esi
    L_0046148a:
        call asm_fclose_lk_0046140c
    L_0046148f:
        pop ecx
    L_00461490:
        mov dword ptr [ebp-1Ch],eax
    L_00461493:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461497:
        call asm_target_004614a1
    L_0046149c:
        jmp short L_00461475
    L_0046149e:
        mov esi,dword ptr [ebp+8]
    L_004614a1:
        push esi
    L_004614a2:
        call asm_unassigned_0045a0bc
    L_004614a7:
        pop ecx
    L_004614a8:
        ret
    }
}
