#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004285F0..0x00428626: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004285f0() {
    __asm {
    L_004285f0:
        fld dword ptr [eax]
    L_004285f2:
        fmul dword ptr [data_00470b0c]
    L_004285f8:
        fsubr dword ptr [ecx]
    L_004285fa:
        fstp dword ptr [esi]
    L_004285fc:
        fld dword ptr [eax+4]
    L_004285ff:
        fmul dword ptr [data_00470b0c]
    L_00428605:
        fsubr dword ptr [ecx+4]
    L_00428608:
        fstp dword ptr [esi+4]
    L_0042860b:
        fld dword ptr [eax]
    L_0042860d:
        fmul dword ptr [data_00470b0c]
    L_00428613:
        fadd dword ptr [ecx]
    L_00428615:
        fstp dword ptr [edx]
    L_00428617:
        fld dword ptr [eax+4]
    L_0042861a:
        fmul dword ptr [data_00470b0c]
    L_00428620:
        fadd dword ptr [ecx+4]
    L_00428623:
        fstp dword ptr [edx+4]
    L_00428626:
        ret
    }
}
