#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441DD0..0x00441DF4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441dd0() {
    __asm {
    L_00441dd0:
        fld dword ptr [edx+4]
    L_00441dd3:
        fsub dword ptr [ecx+4]
    L_00441dd6:
        fld dword ptr [edx]
    L_00441dd8:
        fsub dword ptr [ecx]
    L_00441dda:
        fstp dword ptr [eax]
    L_00441ddc:
        fstp dword ptr [eax+4]
    L_00441ddf:
        ret
    L_00441de0:
        fld dword ptr [esp+4]
    L_00441de4:
        fmul dword ptr [ecx+4]
    L_00441de7:
        fld dword ptr [esp+4]
    L_00441deb:
        fmul dword ptr [ecx]
    L_00441ded:
        fstp dword ptr [eax]
    L_00441def:
        fstp dword ptr [eax+4]
    L_00441df2:
        ret 4
    }
}
