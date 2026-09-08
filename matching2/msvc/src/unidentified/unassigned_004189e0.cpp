#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004189E0..0x004189EE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004189e0() {
    __asm {
    L_004189e0:
        xor ecx,ecx
    L_004189e2:
        mov dword ptr [eax+50h],ecx
    L_004189e5:
        mov dword ptr [eax+54h],ecx
    L_004189e8:
        mov dword ptr [eax+4Ch],ecx
    L_004189eb:
        mov dword ptr [eax+58h],ecx
    L_004189ee:
        ret
    }
}
