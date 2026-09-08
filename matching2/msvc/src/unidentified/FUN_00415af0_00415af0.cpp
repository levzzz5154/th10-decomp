#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415AF0..0x00415AF6: FUN_00415af0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415af0_00415af0() {
    __asm {
    L_00415af0:
        push ecx
    L_00415af1:
        call asm_FUN_00415800_00415800
    L_00415af6:
        ret
    }
}
