#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004525FF..0x00452646: `eh_vector_destructor_iterator'
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_eh_vector_destructor_iterator_004525ff() {
    __asm {
    L_004525ff:
        push 0Ch
    L_00452601:
        push 46A6C0h
    L_00452606:
        call asm_SEH_prolog_00454bbc
    L_0045260b:
        and dword ptr [ebp-1Ch],0
    L_0045260f:
        mov esi,dword ptr [ebp+0Ch]
    L_00452612:
        mov eax,esi
    L_00452614:
        imul eax,dword ptr [ebp+10h]
    L_00452618:
        add dword ptr [ebp+8],eax
    L_0045261b:
        and dword ptr [ebp-4],0
    L_0045261f:
        dec dword ptr [ebp+10h]
    L_00452622:
        js short L_0045262f
    L_00452624:
        sub dword ptr [ebp+8],esi
    L_00452627:
        mov ecx,dword ptr [ebp+8]
    L_0045262a:
        call dword ptr [ebp+14h]
    L_0045262d:
        jmp short L_0045261f
    L_0045262f:
        mov dword ptr [ebp-1Ch],1
    L_00452636:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045263a:
        call asm_FUN_00452647_00452647
    L_0045263f:
        call asm_SEH_epilog_00454bf7
    L_00452644:
        ret 10h
    }
}
