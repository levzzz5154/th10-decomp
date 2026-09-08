#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442150..0x00442163: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00442150() {
    __asm {
    L_00442150:
        mov edx,dword ptr [eax]
    L_00442152:
        add ecx,24h
    L_00442155:
        mov dword ptr [ecx],edx
    L_00442157:
        mov edx,dword ptr [eax+4]
    L_0044215a:
        mov dword ptr [ecx+4],edx
    L_0044215d:
        mov eax,dword ptr [eax+8]
    L_00442160:
        mov dword ptr [ecx+8],eax
    L_00442163:
        ret
    }
}
