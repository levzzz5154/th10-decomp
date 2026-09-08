#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459F15..0x00459F1C: FUN_00459f15
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00459f15_00459f15() {
    __asm {
    L_00459f15:
        push ebx
    L_00459f16:
        call asm_FUN_0045f7b5_0045f7b5
    L_00459f1b:
        pop ecx
    L_00459f1c:
        ret
    }
}
