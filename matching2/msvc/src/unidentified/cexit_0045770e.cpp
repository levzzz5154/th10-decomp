#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045770E..0x0045771C: __cexit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cexit_0045770e() {
    __asm {
    L_0045770e:
        push 1
    L_00457710:
        push 0
    L_00457712:
        push 0
    L_00457714:
        call asm_doexit_00457629
    L_00457719:
        add esp,0Ch
    L_0045771c:
        ret
    }
}
