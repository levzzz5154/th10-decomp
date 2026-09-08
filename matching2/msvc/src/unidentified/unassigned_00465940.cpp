#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465940..0x0046594B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465940() {
    __asm {
    L_00465940:
        push 465A20h
    L_00465945:
        call asm_atexit_00452e0a
    L_0046594a:
        pop ecx
    L_0046594b:
        ret
    }
}
