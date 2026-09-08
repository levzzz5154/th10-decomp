#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DA0..0x00421DA7: FUN_00421da0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421da0_00421da0() {
    __asm {
    L_00421da0:
        mov byte ptr [eax+3ADA6Ch],0FFh
    L_00421da7:
        ret
    }
}
