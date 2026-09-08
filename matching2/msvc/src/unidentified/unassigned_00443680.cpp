#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443680..0x004436B3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00443680() {
    __asm {
    L_00443680:
        fld dword ptr [esp+4]
    L_00443684:
        fmul dword ptr [esp+10h]
    L_00443688:
        fld dword ptr [esp+8]
    L_0044368c:
        fmul dword ptr [esp+0Ch]
    L_00443690:
        fsubp st(1),st
    L_00443692:
        fadd dword ptr [esp+14h]
    L_00443696:
        fstp dword ptr [eax]
    L_00443698:
        fld dword ptr [esp+4]
    L_0044369c:
        fmul dword ptr [esp+0Ch]
    L_004436a0:
        fld dword ptr [esp+8]
    L_004436a4:
        fmul dword ptr [esp+10h]
    L_004436a8:
        faddp st(1),st
    L_004436aa:
        fadd dword ptr [esp+18h]
    L_004436ae:
        fstp dword ptr [eax+4]
    L_004436b1:
        ret 18h
    }
}
