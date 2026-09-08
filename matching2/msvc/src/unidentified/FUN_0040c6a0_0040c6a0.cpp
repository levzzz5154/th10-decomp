#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C6A0..0x0040C6A4: FUN_0040c6a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c6a0_0040c6a0() {
    __asm {
    L_0040c6a0:
        xor eax,eax
    L_0040c6a2:
        ret 4
    }
}
