#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004597A3..0x004597A9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004597a3() {
    __asm {
    L_004597a3:
        xor eax,eax
    L_004597a5:
        inc eax
    L_004597a6:
        ret
    L_004597a7:
        mov esp,dword ptr [ebp-18h]
    }
}
