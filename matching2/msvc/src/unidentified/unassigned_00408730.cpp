#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408730..0x00408748: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408730() {
    __asm {
    L_00408730:
        fld dword ptr [eax]
    L_00408732:
        fsub dword ptr [ecx]
    L_00408734:
        fstp dword ptr [eax]
    L_00408736:
        fld dword ptr [eax+4]
    L_00408739:
        fsub dword ptr [ecx+4]
    L_0040873c:
        fstp dword ptr [eax+4]
    L_0040873f:
        fld dword ptr [eax+8]
    L_00408742:
        fsub dword ptr [ecx+8]
    L_00408745:
        fstp dword ptr [eax+8]
    L_00408748:
        ret
    }
}
