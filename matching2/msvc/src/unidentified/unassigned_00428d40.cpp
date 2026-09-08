#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428D40..0x00428D58: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428d40() {
    __asm {
    L_00428d40:
        fld dword ptr [ecx+4]
    L_00428d43:
        fsub dword ptr [eax+4]
    L_00428d46:
        fld dword ptr [ecx]
    L_00428d48:
        fsub dword ptr [eax]
    L_00428d4a:
        fld st(0)
    L_00428d4c:
        fmul st,st(1)
    L_00428d4e:
        fld st(2)
    L_00428d50:
        fmul st,st(3)
    L_00428d52:
        faddp st(1),st
    L_00428d54:
        fstp st(2)
    L_00428d56:
        fstp st(0)
    L_00428d58:
        ret
    }
}
