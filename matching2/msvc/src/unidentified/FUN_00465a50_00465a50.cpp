#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A50..0x00465A5A: FUN_00465a50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a50_00465a50() {
    __asm {
    L_00465a50:
        push 492548h
    L_00465a55:
        call asm_Recovery_ReleaseRawPair_0043cb00
    L_00465a5a:
        ret
    }
}
