#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041EAF0..0x0041EAF2: FUN_0041eaf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041eaf0_0041eaf0() {
    __asm {
    L_0041eaf0:
        xor eax,eax
    L_0041eaf2:
        ret
    }
}
