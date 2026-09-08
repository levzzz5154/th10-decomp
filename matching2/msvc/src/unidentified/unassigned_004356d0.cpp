#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004356D0..0x004356E3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004356d0() {
    __asm {
    L_004356d0:
        push 2Fh
    L_004356d2:
        push esi
    L_004356d3:
        call asm_FUN_00452730_00452730
    L_004356d8:
        add esp,8
    L_004356db:
        test eax,eax
    L_004356dd:
        je short L_004356e1
    L_004356df:
        inc eax
    L_004356e0:
        ret
    L_004356e1:
        mov eax,esi
    L_004356e3:
        ret
    }
}
