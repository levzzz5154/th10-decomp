#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457580..0x00457588: FUN_00457580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457580_00457580() {
    __asm {
    L_00457580:
        push 8
    L_00457582:
        call asm_FUN_00453b3f_00453b3f
    L_00457587:
        pop ecx
    L_00457588:
        ret
    }
}
