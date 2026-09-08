#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C6C0..0x0040C6C4: FUN_0040c6c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c6c0_0040c6c0() {
    __asm {
    L_0040c6c0:
        xor eax,eax
    L_0040c6c2:
        ret 4
    }
}
