#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412E30..0x00412E54: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412e30() {
    __asm {
    L_00412e30:
        fld dword ptr [edx+4]
    L_00412e33:
        fsub dword ptr [ecx+4]
    L_00412e36:
        fld dword ptr [edx]
    L_00412e38:
        fsub dword ptr [ecx]
    L_00412e3a:
        fstp dword ptr [eax]
    L_00412e3c:
        fstp dword ptr [eax+4]
    L_00412e3f:
        ret
    L_00412e40:
        fld dword ptr [esp+4]
    L_00412e44:
        fmul dword ptr [ecx+4]
    L_00412e47:
        fld dword ptr [esp+4]
    L_00412e4b:
        fmul dword ptr [ecx]
    L_00412e4d:
        fstp dword ptr [eax]
    L_00412e4f:
        fstp dword ptr [eax+4]
    L_00412e52:
        ret 4
    }
}
