#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405020..0x00405033: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405020() {
    __asm {
    L_00405020:
        mov edx,dword ptr [eax]
    L_00405022:
        add ecx,18h
    L_00405025:
        mov dword ptr [ecx],edx
    L_00405027:
        mov edx,dword ptr [eax+4]
    L_0040502a:
        mov dword ptr [ecx+4],edx
    L_0040502d:
        mov eax,dword ptr [eax+8]
    L_00405030:
        mov dword ptr [ecx+8],eax
    L_00405033:
        ret
    }
}
