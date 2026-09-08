#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004051B0..0x004051B6: FUN_004051b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004051b0_004051b0() {
    __asm {
    L_004051b0:
        mov byte ptr [eax+3ADA6Ch],cl
    L_004051b6:
        ret
    }
}
