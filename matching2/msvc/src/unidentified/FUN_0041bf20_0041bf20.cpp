#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF20..0x0041BF22: FUN_0041bf20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf20_0041bf20() {
    __asm {
    L_0041bf20:
        xor eax,eax
    L_0041bf22:
        ret
    }
}
