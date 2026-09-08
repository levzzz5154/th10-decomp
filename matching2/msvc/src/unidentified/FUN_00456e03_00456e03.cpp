#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456E03..0x00456E0B: FUN_00456e03
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456e03_00456e03() {
    __asm {
    L_00456e03:
        push 7
    L_00456e05:
        call asm_FUN_00453b3f_00453b3f
    L_00456e0a:
        pop ecx
    L_00456e0b:
        ret
    }
}
