#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409E00..0x00409E0B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409e00() {
    __asm {
    L_00409e00:
        mov edx,dword ptr [ecx+10h]
    L_00409e03:
        xor eax,eax
    L_00409e05:
        cmp edx,1
    L_00409e08:
        sete al
    L_00409e0b:
        ret
    }
}
