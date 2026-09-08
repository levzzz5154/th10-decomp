#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464F00..0x00464F14: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464f00() {
    __asm {
    L_00464f00:
        fld st(0)
    L_00464f02:
        frndint
    L_00464f04:
        fsubr st(1),st
    L_00464f06:
        fxch
    L_00464f08:
        fchs
    L_00464f0a:
        f2xm1
    L_00464f0c:
        fld1
    L_00464f0e:
        faddp st(1),st
    L_00464f10:
        fscale
    L_00464f12:
        fstp st(1)
    L_00464f14:
        ret
    }
}
