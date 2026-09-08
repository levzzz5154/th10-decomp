#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C5E0..0x0040C5E2: FUN_0040c5e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c5e0_0040c5e0() {
    __asm {
    L_0040c5e0:
        xor eax,eax
    L_0040c5e2:
        ret
    }
}
