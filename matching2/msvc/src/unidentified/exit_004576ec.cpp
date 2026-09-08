#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004576EC..0x004576FC: _exit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_exit_004576ec() {
    __asm {
    L_004576ec:
        push 0
    L_004576ee:
        push 0
    L_004576f0:
        push dword ptr [esp+0Ch]
    L_004576f4:
        call asm_doexit_00457629
    L_004576f9:
        add esp,0Ch
    L_004576fc:
        ret
    }
}
