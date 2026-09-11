#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x00426610..0x00426652: ?Entity_AngleToPoint@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Entity_AngleToPoint_00426610() {
    __asm {
    L_00426610:
        fld dword ptr [eax]
    L_00426612:
        fsub dword ptr [ecx+3C0h]
    L_00426618:
        fld dword ptr [eax+4]
    L_0042661b:
        fsub dword ptr [ecx+3C4h]
    L_00426621:
        fld dword ptr [data_00470b04]
    L_00426627:
        fld st(1)
    L_00426629:
        fucompp
    L_0042662b:
        fnstsw ax
    L_0042662d:
        test ah,44h
    L_00426630:
        jp short L_0042664e
    L_00426632:
        fld dword ptr [data_00470b04]
    L_00426638:
        fld st(2)
    L_0042663a:
        fucompp
    L_0042663c:
        fnstsw ax
    L_0042663e:
        test ah,44h
    L_00426641:
        jp short L_0042664e
    L_00426643:
        fstp st(0)
    L_00426645:
        fstp st(0)
    L_00426647:
        fld dword ptr [data_00470b94]
    L_0042664d:
        ret
    L_0042664e:
        fxch
    L_00426650:
        fpatan
    L_00426652:
        ret
    }
}
