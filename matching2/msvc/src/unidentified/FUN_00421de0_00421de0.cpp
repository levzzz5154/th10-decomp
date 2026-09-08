#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DE0..0x00421DEA: FUN_00421de0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421de0_00421de0() {
    __asm {
    L_00421de0:
        mov dword ptr [eax+3ADA64h],0
    L_00421dea:
        ret
    }
}
