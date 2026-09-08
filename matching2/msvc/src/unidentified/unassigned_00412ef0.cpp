#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412EF0..0x00412F08: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412ef0() {
    __asm {
    L_00412ef0:
        fld dword ptr [ecx+4]
    L_00412ef3:
        fsub dword ptr [eax+4]
    L_00412ef6:
        fld dword ptr [ecx]
    L_00412ef8:
        fsub dword ptr [eax]
    L_00412efa:
        fld st(0)
    L_00412efc:
        fmul st,st(1)
    L_00412efe:
        fld st(2)
    L_00412f00:
        fmul st,st(3)
    L_00412f02:
        faddp st(1),st
    L_00412f04:
        fstp st(2)
    L_00412f06:
        fstp st(0)
    L_00412f08:
        ret
    }
}
