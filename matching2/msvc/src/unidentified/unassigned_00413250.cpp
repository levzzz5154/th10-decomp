#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413250..0x0041326E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413250() {
    __asm {
    L_00413250:
        fld dword ptr [esp+4]
    L_00413254:
        fmul dword ptr [eax]
    L_00413256:
        fstp dword ptr [eax]
    L_00413258:
        fld dword ptr [esp+4]
    L_0041325c:
        fmul dword ptr [eax+4]
    L_0041325f:
        fstp dword ptr [eax+4]
    L_00413262:
        fld dword ptr [esp+4]
    L_00413266:
        fmul dword ptr [eax+8]
    L_00413269:
        fstp dword ptr [eax+8]
    L_0041326c:
        ret 4
    }
}
