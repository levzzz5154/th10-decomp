#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF80..0x0041BF84: FUN_0041bf80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf80_0041bf80() {
    __asm {
    L_0041bf80:
        xor eax,eax
    L_0041bf82:
        ret 8
    }
}
