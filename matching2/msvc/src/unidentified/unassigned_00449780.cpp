#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449780..0x004497A3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449780() {
    __asm {
    L_00449780:
        mov esi,dword ptr [ecx]
    L_00449782:
        movsx esi,word ptr [esi+38Ah]
    L_00449789:
        cmp esi,edx
    L_0044978b:
        je short L_0044979c
    L_0044978d:
        mov ecx,dword ptr [ecx+4]
    L_00449790:
        test ecx,ecx
    L_00449792:
        jne short L_00449780
    L_00449794:
        mov dword ptr [eax],0
    L_0044979a:
        pop esi
    L_0044979b:
        ret
    L_0044979c:
        mov ecx,dword ptr [ecx]
    L_0044979e:
        mov edx,dword ptr [ecx]
    L_004497a0:
        mov dword ptr [eax],edx
    L_004497a2:
        pop esi
    L_004497a3:
        ret
    }
}
