#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461549..0x00461550: FUN_00461549
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461549_00461549() {
    __asm {
    L_00461549:
        push ebx
    L_0046154a:
        call asm_FUN_0045f7b5_0045f7b5
    L_0046154f:
        pop ecx
    L_00461550:
        ret
    }
}
