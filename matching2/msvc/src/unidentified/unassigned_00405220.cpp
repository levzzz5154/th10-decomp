#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405220..0x0040523E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405220() {
    __asm {
    L_00405220:
        fld dword ptr [eax+8]
    L_00405223:
        fld dword ptr [eax+4]
    L_00405226:
        fld dword ptr [eax]
    L_00405228:
        fld st(0)
    L_0040522a:
        fmul st,st(1)
    L_0040522c:
        fld st(2)
    L_0040522e:
        fmul st,st(3)
    L_00405230:
        faddp st(1),st
    L_00405232:
        fld st(3)
    L_00405234:
        fmul st,st(4)
    L_00405236:
        faddp st(1),st
    L_00405238:
        fstp st(3)
    L_0040523a:
        fstp st(0)
    L_0040523c:
        fstp st(0)
    L_0040523e:
        ret
    }
}
