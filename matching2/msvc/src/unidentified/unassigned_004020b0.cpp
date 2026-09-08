#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004020B0..0x004020E7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004020b0() {
    __asm {
    L_004020b0:
        mov edx,dword ptr [eax+6Ch]
    L_004020b3:
        mov ecx,0FFFFFFFEh
    L_004020b8:
        and edx,ecx
    L_004020ba:
        mov dword ptr [eax+6Ch],edx
    L_004020bd:
        and dword ptr [eax+0B0h],ecx
    L_004020c3:
        and dword ptr [eax+0FCh],ecx
    L_004020c9:
        and dword ptr [eax+128h],ecx
    L_004020cf:
        and dword ptr [eax+174h],ecx
    L_004020d5:
        and dword ptr [eax+1B0h],ecx
    L_004020db:
        and dword ptr [eax+1FCh],ecx
    L_004020e1:
        and dword ptr [eax+228h],ecx
    L_004020e7:
        ret
    }
}
