#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422AA0..0x00422AA6: FUN_00422aa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422aa0_00422aa0() {
    __asm {
    L_00422aa0:
        push ecx
    L_00422aa1:
        call asm_FUN_00422660_00422660
    L_00422aa6:
        ret
    }
}
