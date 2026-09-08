#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004598BC..0x004598DD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004598bc() {
    __asm {
    L_004598bc:
        mov ecx,dword ptr [esp+4]
    L_004598c0:
        test dword ptr [ecx+4],6
    L_004598c7:
        mov eax,1
    L_004598cc:
        je short L_004598dd
    L_004598ce:
        mov eax,dword ptr [esp+8]
    L_004598d2:
        mov edx,dword ptr [esp+10h]
    L_004598d6:
        mov dword ptr [edx],eax
    L_004598d8:
        mov eax,3
    L_004598dd:
        ret
    }
}
