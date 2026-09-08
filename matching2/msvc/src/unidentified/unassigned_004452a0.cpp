#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004452A0..0x004452C0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004452a0() {
    __asm {
    L_004452a0:
        fld dword ptr [eax+8]
    L_004452a3:
        fld dword ptr [eax+4]
    L_004452a6:
        fld dword ptr [eax]
    L_004452a8:
        fld st(0)
    L_004452aa:
        fmul st,st(1)
    L_004452ac:
        fld st(2)
    L_004452ae:
        fmul st,st(3)
    L_004452b0:
        faddp st(1),st
    L_004452b2:
        fld st(3)
    L_004452b4:
        fmul st,st(4)
    L_004452b6:
        faddp st(1),st
    L_004452b8:
        fsqrt
    L_004452ba:
        fstp st(3)
    L_004452bc:
        fstp st(0)
    L_004452be:
        fstp st(0)
    L_004452c0:
        ret
    }
}
