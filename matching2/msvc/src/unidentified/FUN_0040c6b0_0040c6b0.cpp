#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C6B0..0x0040C6B8: FUN_0040c6b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c6b0_0040c6b0() {
    __asm {
    L_0040c6b0:
        fld dword ptr [data_00470b04]
    L_0040c6b6:
        ret 4
    }
}
