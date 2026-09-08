#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457799..0x004577A1: FUN_00457799
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457799_00457799() {
    __asm {
    L_00457799:
        push 4
    L_0045779b:
        call asm_FUN_00453b3f_00453b3f
    L_004577a0:
        pop ecx
    L_004577a1:
        ret
    }
}
