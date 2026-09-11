#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x00426660..0x004266A2: ?Entity_AngleFromPoint@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_AngleFromPoint_00426660() {
    __asm {
    L_00426660:
        fld dword ptr [ecx+3C0h]
    L_00426666:
        fsub dword ptr [eax]
    L_00426668:
        fld dword ptr [ecx+3C4h]
    L_0042666e:
        fsub dword ptr [eax+4]
    L_00426671:
        fld dword ptr [data_00470b04]
    L_00426677:
        fld st(1)
    L_00426679:
        fucompp
    L_0042667b:
        fnstsw ax
    L_0042667d:
        test ah,44h
    L_00426680:
        jp short L_0042669e
    L_00426682:
        fld dword ptr [data_00470b04]
    L_00426688:
        fld st(2)
    L_0042668a:
        fucompp
    L_0042668c:
        fnstsw ax
    L_0042668e:
        test ah,44h
    L_00426691:
        jp short L_0042669e
    L_00426693:
        fstp st(0)
    L_00426695:
        fstp st(0)
    L_00426697:
        fld dword ptr [data_00470b94]
    L_0042669d:
        ret
    L_0042669e:
        fxch
    L_004266a0:
        fpatan
    L_004266a2:
        ret
    }
}
