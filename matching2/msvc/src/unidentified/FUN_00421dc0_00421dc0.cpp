#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DC0..0x00421DC7: FUN_00421dc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421dc0_00421dc0() {
    __asm {
    L_00421dc0:
        mov byte ptr [eax+3ADA68h],3
    L_00421dc7:
        ret
    }
}
