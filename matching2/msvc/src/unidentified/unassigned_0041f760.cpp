#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F760..0x0041F778: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041f760() {
    __asm {
    L_0041f760:
        fld dword ptr [ecx+4]
    L_0041f763:
        fsub dword ptr [eax+4]
    L_0041f766:
        fld dword ptr [ecx]
    L_0041f768:
        fsub dword ptr [eax]
    L_0041f76a:
        fld st(0)
    L_0041f76c:
        fmul st,st(1)
    L_0041f76e:
        fld st(2)
    L_0041f770:
        fmul st,st(3)
    L_0041f772:
        faddp st(1),st
    L_0041f774:
        fstp st(2)
    L_0041f776:
        fstp st(0)
    L_0041f778:
        ret
    }
}
