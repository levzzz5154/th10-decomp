#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DB0..0x00421DB7: FUN_00421db0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421db0_00421db0() {
    __asm {
    L_00421db0:
        mov byte ptr [eax+3ADA6Bh],0FFh
    L_00421db7:
        ret
    }
}
