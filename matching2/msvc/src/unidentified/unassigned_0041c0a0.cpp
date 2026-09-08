#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C0A0..0x0041C0C8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c0a0() {
    __asm {
    L_0041c0a0:
        push esi
    L_0041c0a1:
        push edi
    L_0041c0a2:
        mov ecx,77h
    L_0041c0a7:
        mov esi,edx
    L_0041c0a9:
        mov edi,eax
    L_0041c0ab:
        rep movsd
    L_0041c0ad:
        pop edi
    L_0041c0ae:
        pop esi
    L_0041c0af:
        ret
    L_0041c0b0:
        mov edx,dword ptr [eax+434h]
    L_0041c0b6:
        mov dword ptr [ecx+4],edx
    L_0041c0b9:
        mov dword ptr [edx+8],ecx
    L_0041c0bc:
        mov dword ptr [eax+434h],ecx
    L_0041c0c2:
        inc dword ptr [eax+438h]
    L_0041c0c8:
        ret
    }
}
