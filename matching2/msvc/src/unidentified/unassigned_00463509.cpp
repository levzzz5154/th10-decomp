#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463509..0x00463514: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463509() {
    __asm {
    L_00463509:
        xor eax,eax
    L_0046350b:
        inc eax
    L_0046350c:
        ret
    L_0046350d:
        mov esp,dword ptr [ebp-18h]
    L_00463510:
        jmp asm_terminate_00455693
    }
}
