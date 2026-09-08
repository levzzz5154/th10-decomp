#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004369E0..0x00436A10: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004369e0() {
    __asm {
    L_004369e0:
        xor ecx,ecx
    L_004369e2:
        mov dword ptr [eax+100h],0FFFFFFFFh
    L_004369ec:
        mov dword ptr [eax+104h],ecx
    L_004369f2:
        mov dword ptr [eax+108h],ecx
    L_004369f8:
        mov dword ptr [eax+114h],ecx
    L_004369fe:
        mov dword ptr [eax+11Ch],ecx
    L_00436a04:
        mov dword ptr [eax+118h],ecx
    L_00436a0a:
        mov dword ptr [eax+120h],ecx
    L_00436a10:
        ret
    }
}
