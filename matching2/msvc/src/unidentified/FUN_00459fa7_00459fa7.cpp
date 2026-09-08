#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459FA7..0x00459FAC: FUN_00459fa7
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00459fa7_00459fa7() {
    __asm {
    L_00459fa7:
        mov eax,473740h
    L_00459fac:
        ret
    }
}
