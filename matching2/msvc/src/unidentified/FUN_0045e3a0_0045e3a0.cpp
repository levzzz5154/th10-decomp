#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E3A0..0x0045E3A2: FUN_0045e3a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045e3a0_0045e3a0() {
    __asm {
    L_0045e3a0:
        xor eax,eax
    L_0045e3a2:
        ret
    }
}
