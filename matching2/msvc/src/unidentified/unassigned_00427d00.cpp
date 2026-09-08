#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427D00..0x00427D21: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427d00() {
    __asm {
    L_00427d00:
        push esi
    L_00427d01:
        mov esi,dword ptr [edx]
    L_00427d03:
        push edi
    L_00427d04:
        mov edi,dword ptr [ecx]
    L_00427d06:
        add edi,esi
    L_00427d08:
        mov esi,dword ptr [ecx+4]
    L_00427d0b:
        mov dword ptr [ecx],edi
    L_00427d0d:
        mov edx,dword ptr [edx+4]
    L_00427d10:
        add esi,edx
    L_00427d12:
        mov dword ptr [ecx+4],esi
    L_00427d15:
        mov edx,edi
    L_00427d17:
        mov dword ptr [eax],edx
    L_00427d19:
        mov ecx,dword ptr [ecx+4]
    L_00427d1c:
        pop edi
    L_00427d1d:
        mov dword ptr [eax+4],ecx
    L_00427d20:
        pop esi
    L_00427d21:
        ret
    }
}
