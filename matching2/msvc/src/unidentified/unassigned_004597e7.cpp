#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004597E7..0x004597ED: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004597e7() {
    __asm {
    L_004597e7:
        xor eax,eax
    L_004597e9:
        inc eax
    L_004597ea:
        ret
    L_004597eb:
        mov esp,dword ptr [ebp-18h]
    }
}
