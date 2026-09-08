#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449440..0x0044944A: FUN_00449440
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449440_00449440() {
    __asm {
    L_00449440:
        mov ecx,dword ptr [data_00491c10]
    L_00449446:
        jmp asm_FUN_004451c0_004451c0
    }
}
