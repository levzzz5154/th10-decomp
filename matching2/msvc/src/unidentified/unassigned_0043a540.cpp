#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A540..0x0043A56D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a540() {
    __asm {
    L_0043a540:
        mov eax,dword ptr [edi]
    L_0043a542:
        test eax,eax
    L_0043a544:
        jne short L_0043a547
    L_0043a546:
        ret
    L_0043a547:
        push 40h
    L_0043a549:
        push esi
    L_0043a54a:
        push eax
    L_0043a54b:
        call dword ptr [data_004662a0]
    L_0043a551:
        test eax,eax
    L_0043a553:
        je short L_0043a55b
    L_0043a555:
        mov eax,1
    L_0043a55a:
        ret
    L_0043a55b:
        mov eax,dword ptr [edi]
    L_0043a55d:
        push 40h
    L_0043a55f:
        push esi
    L_0043a560:
        push eax
    L_0043a561:
        call dword ptr [data_0046629c]
    L_0043a567:
        neg eax
    L_0043a569:
        sbb eax,eax
    L_0043a56b:
        neg eax
    L_0043a56d:
        ret
    }
}
