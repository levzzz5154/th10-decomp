#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FEF0..0x0041FEF6: FUN_0041fef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041fef0_0041fef0() {
    __asm {
    L_0041fef0:
        push ecx
    L_0041fef1:
        call asm_FUN_0041fdd0_0041fdd0
    L_0041fef6:
        ret
    }
}
