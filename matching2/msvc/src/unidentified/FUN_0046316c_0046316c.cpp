#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046316C..0x0046316F: FUN_0046316c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046316c_0046316c() {
    __asm {
    L_0046316c:
        push 10h
    L_0046316e:
        pop eax
    L_0046316f:
        ret
    }
}
