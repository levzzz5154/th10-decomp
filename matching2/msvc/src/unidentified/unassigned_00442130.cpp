#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442130..0x00442143: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00442130() {
    __asm {
    L_00442130:
        mov edx,dword ptr [eax]
    L_00442132:
        add ecx,18h
    L_00442135:
        mov dword ptr [ecx],edx
    L_00442137:
        mov edx,dword ptr [eax+4]
    L_0044213a:
        mov dword ptr [ecx+4],edx
    L_0044213d:
        mov eax,dword ptr [eax+8]
    L_00442140:
        mov dword ptr [ecx+8],eax
    L_00442143:
        ret
    }
}
