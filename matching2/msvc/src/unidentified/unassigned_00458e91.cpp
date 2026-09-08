#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458E91..0x00458E97: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00458e91() {
    __asm {
    L_00458e91:
        xor eax,eax
    L_00458e93:
        inc eax
    L_00458e94:
        ret
    L_00458e95:
        mov esp,dword ptr [ebp-18h]
    }
}
