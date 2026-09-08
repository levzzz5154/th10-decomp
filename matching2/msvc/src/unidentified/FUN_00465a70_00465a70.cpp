#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A70..0x00465A70: FUN_00465a70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a70_00465a70() {
    __asm {
    L_00465a70:
        ret
    }
}
