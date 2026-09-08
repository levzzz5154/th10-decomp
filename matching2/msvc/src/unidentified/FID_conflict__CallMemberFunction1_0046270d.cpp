#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046270D..0x00462713: FID_conflict:_CallMemberFunction1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict__CallMemberFunction1_0046270d() {
    __asm {
    L_0046270d:
        pop eax
    L_0046270e:
        pop ecx
    L_0046270f:
        xchg eax,dword ptr [esp]
    L_00462712:
        jmp eax
    }
}
