#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F3B4..0x0045F3BF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f3b4() {
    __asm {
    L_0045f3b4:
        push 0
    L_0045f3b6:
        push 1
    L_0045f3b8:
        call asm_FUN_0045f259_0045f259
    L_0045f3bd:
        pop ecx
    L_0045f3be:
        pop ecx
    L_0045f3bf:
        ret
    }
}
