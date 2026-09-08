#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF10..0x0041BF12: FUN_0041bf10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf10_0041bf10() {
    __asm {
    L_0041bf10:
        xor eax,eax
    L_0041bf12:
        ret
    }
}
