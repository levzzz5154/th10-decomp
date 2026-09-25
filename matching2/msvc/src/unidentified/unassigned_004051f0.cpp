#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004051F0..0x00405218: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004051f0() {
    __asm {
    L_004051f0:
        fld dword ptr [data_00470afc]
    L_004051f6:
        fdiv dword ptr [esp+4]
    L_004051fa:
        fst dword ptr [esp+4]
    L_004051fe:
        fmul dword ptr [ecx+8]
    L_00405201:
        fld dword ptr [esp+4]
    L_00405205:
        fmul dword ptr [ecx+4]
    L_00405208:
        fld dword ptr [esp+4]
    L_0040520c:
        fmul dword ptr [ecx]
    L_0040520e:
        fstp dword ptr [eax]
    L_00405210:
        fstp dword ptr [eax+4]
    L_00405213:
        fstp dword ptr [eax+8]
    L_00405216:
        ret 4
    }
}
