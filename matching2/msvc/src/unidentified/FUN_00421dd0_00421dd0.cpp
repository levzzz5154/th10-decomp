#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DD0..0x00421DD7: FUN_00421dd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421dd0_00421dd0() {
    __asm {
    L_00421dd0:
        mov byte ptr [eax+3ADA69h],0FFh
    L_00421dd7:
        ret
    }
}
