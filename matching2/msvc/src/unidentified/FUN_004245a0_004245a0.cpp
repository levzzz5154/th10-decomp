#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245A0..0x004245A6: FUN_004245a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004245a0_004245a0() {
    __asm {
    L_004245a0:
        mov dword ptr [eax+8988h],ecx
    L_004245a6:
        ret
    }
}
