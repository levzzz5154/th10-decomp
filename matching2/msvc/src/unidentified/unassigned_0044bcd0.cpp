#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BCD0..0x0044BCF7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bcd0() {
    __asm {
    L_0044bcd0:
        fld dword ptr [esp+4]
    L_0044bcd4:
        fsin
    L_0044bcd6:
        fld dword ptr [esp+4]
    L_0044bcda:
        fcos
    L_0044bcdc:
        fld st(0)
    L_0044bcde:
        fmul dword ptr [eax]
    L_0044bce0:
        fld st(2)
    L_0044bce2:
        fmul dword ptr [eax+4]
    L_0044bce5:
        fsubp st(1),st
    L_0044bce7:
        fstp dword ptr [ecx]
    L_0044bce9:
        fmul dword ptr [eax+4]
    L_0044bcec:
        fxch
    L_0044bcee:
        fmul dword ptr [eax]
    L_0044bcf0:
        faddp st(1),st
    L_0044bcf2:
        fstp dword ptr [ecx+4]
    L_0044bcf5:
        ret 4
    }
}
