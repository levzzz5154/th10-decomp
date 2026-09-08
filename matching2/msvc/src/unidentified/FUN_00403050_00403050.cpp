#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403050..0x00403056: FUN_00403050
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403050_00403050() {
    __asm {
    L_00403050:
        mov eax,ecx
    L_00403052:
        jmp asm_FUN_00402720_00402720
    }
}
