#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004576FD..0x0045770D: __exit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_exit_004576fd() {
    __asm {
    L_004576fd:
        push 0
    L_004576ff:
        push 1
    L_00457701:
        push dword ptr [esp+0Ch]
    L_00457705:
        call asm_doexit_00457629
    L_0045770a:
        add esp,0Ch
    L_0045770d:
        ret
    }
}
