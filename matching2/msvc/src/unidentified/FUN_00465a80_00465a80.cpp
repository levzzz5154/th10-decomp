#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A80..0x00465A80: FUN_00465a80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a80_00465a80() {
    __asm {
    L_00465a80:
        ret
    }
}
