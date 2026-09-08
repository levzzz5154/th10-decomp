#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458B3F..0x00458B45: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00458b3f() {
    __asm {
    L_00458b3f:
        xor eax,eax
    L_00458b41:
        inc eax
    L_00458b42:
        ret
    L_00458b43:
        mov esp,dword ptr [ebp-18h]
    }
}
