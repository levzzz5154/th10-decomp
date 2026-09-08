#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405110..0x00405123: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405110() {
    __asm {
    L_00405110:
        mov edx,dword ptr [eax]
    L_00405112:
        add ecx,0Ch
    L_00405115:
        mov dword ptr [ecx],edx
    L_00405117:
        mov edx,dword ptr [eax+4]
    L_0040511a:
        mov dword ptr [ecx+4],edx
    L_0040511d:
        mov eax,dword ptr [eax+8]
    L_00405120:
        mov dword ptr [ecx+8],eax
    L_00405123:
        ret
    }
}
