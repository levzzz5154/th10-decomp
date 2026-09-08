#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004526D1..0x004526D9: FUN_004526d1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004526d1_004526d1() {
    __asm {
    L_004526d1:
        push 4
    L_004526d3:
        call asm_FUN_00453b3f_00453b3f
    L_004526d8:
        pop ecx
    L_004526d9:
        ret
    }
}
