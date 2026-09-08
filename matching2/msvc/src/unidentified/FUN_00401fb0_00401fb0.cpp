#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401FB0..0x00401FB6: FUN_00401fb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401fb0_00401fb0() {
    __asm {
    L_00401fb0:
        mov dword ptr [eax+898Ch],ecx
    L_00401fb6:
        ret
    }
}
