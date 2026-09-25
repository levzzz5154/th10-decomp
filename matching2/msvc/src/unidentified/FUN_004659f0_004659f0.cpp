#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004659F0..0x004659F9: FUN_004659f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004659f0_004659f0() {
    __asm {
    L_004659f0:
        mov eax,491C28h
    L_004659f5:
        jmp asm_FUN_0041ff60_0041ff60
    }
}
