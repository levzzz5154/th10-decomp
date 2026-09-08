#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453C03..0x00453C0B: FUN_00453c03
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00453c03_00453c03() {
    __asm {
    L_00453c03:
        push 0Ah
    L_00453c05:
        call asm_FUN_00453b3f_00453b3f
    L_00453c0a:
        pop ecx
    L_00453c0b:
        ret
    }
}
