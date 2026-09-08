#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404E70..0x00404E8E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404e70() {
    __asm {
    L_00404e70:
        fld dword ptr [esp+4]
    L_00404e74:
        fmul dword ptr [ecx+8]
    L_00404e77:
        fld dword ptr [esp+4]
    L_00404e7b:
        fmul dword ptr [ecx+4]
    L_00404e7e:
        fld dword ptr [esp+4]
    L_00404e82:
        fmul dword ptr [ecx]
    L_00404e84:
        fstp dword ptr [eax]
    L_00404e86:
        fstp dword ptr [eax+4]
    L_00404e89:
        fstp dword ptr [eax+8]
    L_00404e8c:
        ret 4
    }
}
