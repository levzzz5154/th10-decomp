#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455B10..0x00455B18: FUN_00455b10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455b10_00455b10() {
    __asm {
    L_00455b10:
        push 0Ch
    L_00455b12:
        call asm_FUN_00453b3f_00453b3f
    L_00455b17:
        pop ecx
    L_00455b18:
        ret
    }
}
