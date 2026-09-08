#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408620..0x00408638: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408620() {
    __asm {
    L_00408620:
        fld dword ptr [ecx+4]
    L_00408623:
        fsub dword ptr [eax+4]
    L_00408626:
        fld dword ptr [ecx]
    L_00408628:
        fsub dword ptr [eax]
    L_0040862a:
        fld st(0)
    L_0040862c:
        fmul st,st(1)
    L_0040862e:
        fld st(2)
    L_00408630:
        fmul st,st(3)
    L_00408632:
        faddp st(1),st
    L_00408634:
        fstp st(2)
    L_00408636:
        fstp st(0)
    L_00408638:
        ret
    }
}
