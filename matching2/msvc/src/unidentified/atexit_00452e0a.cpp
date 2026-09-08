#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452E0A..0x00452E1B: _atexit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_atexit_00452e0a() {
    __asm {
    L_00452e0a:
        push dword ptr [esp+4]
    L_00452e0e:
        call asm_onexit_00452dd2
    L_00452e13:
        neg eax
    L_00452e15:
        sbb eax,eax
    L_00452e17:
        neg eax
    L_00452e19:
        pop ecx
    L_00452e1a:
        dec eax
    L_00452e1b:
        ret
    }
}
