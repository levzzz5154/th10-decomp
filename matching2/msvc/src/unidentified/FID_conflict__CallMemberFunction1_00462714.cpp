#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462714..0x0046271A: FID_conflict:_CallMemberFunction1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict__CallMemberFunction1_00462714() {
    __asm {
    L_00462714:
        pop eax
    L_00462715:
        pop ecx
    L_00462716:
        xchg eax,dword ptr [esp]
    L_00462719:
        jmp eax
    }
}
