#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456A8B..0x00456A8B: FUN_00456a8b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456a8b_00456a8b() {
    __asm {
    L_00456a8b:
        ret
    }
}
