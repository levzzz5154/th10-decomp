#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C510..0x0041C5A8: FUN_0041c510
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c510_0041c510() {
    __asm {
    L_0041c510:
        cmp dword ptr [esi+438h],100h
    L_0041c51a:
        jl short L_0041c521
    L_0041c51c:
        xor eax,eax
    L_0041c51e:
        ret 4
    L_0041c521:
        inc dword ptr [esi+43Ch]
    L_0041c527:
        jne short L_0041c533
    L_0041c529:
        mov dword ptr [esi+43Ch],1
    L_0041c533:
        mov eax,dword ptr [esp+4]
    L_0041c537:
        sub eax,0
    L_0041c53a:
        push ebx
    L_0041c53b:
        je short L_0041c55a
    L_0041c53d:
        dec eax
    L_0041c53e:
        jne short L_0041c59f
    L_0041c540:
        push 0D74h
    L_0041c545:
        call asm_operator_new_00452493
    L_0041c54a:
        add esp,4
    L_0041c54d:
        test eax,eax
    L_0041c54f:
        je short L_0041c574
    L_0041c551:
        mov ebx,eax
    L_0041c553:
        call asm_FUN_0041c680_0041c680
    L_0041c558:
        jmp short L_0041c576
    L_0041c55a:
        push 0D58h
    L_0041c55f:
        call asm_operator_new_00452493
    L_0041c564:
        add esp,4
    L_0041c567:
        test eax,eax
    L_0041c569:
        je short L_0041c574
    L_0041c56b:
        mov ebx,eax
    L_0041c56d:
        call asm_ScoreExtendedObject_Initialize_0041c5b0
    L_0041c572:
        jmp short L_0041c576
    L_0041c574:
        xor eax,eax
    L_0041c576:
        mov ecx,dword ptr [esi+43Ch]
    L_0041c57c:
        mov dword ptr [eax+54h],ecx
    L_0041c57f:
        mov ecx,dword ptr [esi+434h]
    L_0041c585:
        mov dword ptr [eax+4],ecx
    L_0041c588:
        mov dword ptr [ecx+8],eax
    L_0041c58b:
        inc dword ptr [esi+438h]
    L_0041c591:
        mov dword ptr [esi+434h],eax
    L_0041c597:
        mov edx,dword ptr [eax]
    L_0041c599:
        mov ecx,eax
    L_0041c59b:
        push edi
    L_0041c59c:
        call dword ptr [edx+4]
    L_0041c59f:
        mov eax,dword ptr [esi+43Ch]
    L_0041c5a5:
        pop ebx
    L_0041c5a6:
        ret 4
    }
}
