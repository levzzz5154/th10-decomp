#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456AFB..0x00456B03: FUN_00456afb
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456afb_00456afb() {
    __asm {
    L_00456afb:
        call asm_getptd_00456357
    L_00456b00:
        add eax,0Ch
    L_00456b03:
        ret
    }
}
