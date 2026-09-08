#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF00..0x0041BF04: FUN_0041bf00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf00_0041bf00() {
    __asm {
    L_0041bf00:
        xor eax,eax
    L_0041bf02:
        ret 4
    }
}
