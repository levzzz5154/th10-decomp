#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A13..0x00457A1B: FUN_00457a13
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457a13_00457a13() {
    __asm {
    L_00457a13:
        push 4
    L_00457a15:
        call asm_FUN_00453b3f_00453b3f
    L_00457a1a:
        pop ecx
    L_00457a1b:
        ret
    }
}
