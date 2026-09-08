#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462706..0x0046270C: _CallMemberFunction0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallMemberFunction0_00462706() {
    __asm {
    L_00462706:
        pop eax
    L_00462707:
        pop ecx
    L_00462708:
        xchg eax,dword ptr [esp]
    L_0046270b:
        jmp eax
    }
}
