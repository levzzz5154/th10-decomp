#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045771D..0x0045772B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045771d() {
    __asm {
    L_0045771d:
        push 1
    L_0045771f:
        push 1
    L_00457721:
        push 0
    L_00457723:
        call asm_doexit_00457629
    L_00457728:
        add esp,0Ch
    L_0045772b:
        ret
    }
}
