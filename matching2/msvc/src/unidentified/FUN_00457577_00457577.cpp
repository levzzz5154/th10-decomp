#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457577..0x0045757F: FUN_00457577
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457577_00457577() {
    __asm {
    L_00457577:
        push 8
    L_00457579:
        call asm_lock_00453c0c
    L_0045757e:
        pop ecx
    L_0045757f:
        ret
    }
}
