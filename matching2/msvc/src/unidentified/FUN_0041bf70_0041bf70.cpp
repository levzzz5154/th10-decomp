#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF70..0x0041BF74: FUN_0041bf70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf70_0041bf70() {
    __asm {
    L_0041bf70:
        xor eax,eax
    L_0041bf72:
        ret 4
    }
}
