#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415AE0..0x00415AE6: FUN_00415ae0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415ae0_00415ae0() {
    __asm {
    L_00415ae0:
        push ecx
    L_00415ae1:
        call asm_FUN_00414900_00414900
    L_00415ae6:
        ret
    }
}
