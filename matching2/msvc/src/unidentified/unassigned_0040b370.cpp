#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B370..0x0040B386: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b370() {
    __asm {
    L_0040b370:
        mov edx,dword ptr [eax]
    L_0040b372:
        add ecx,340h
    L_0040b378:
        mov dword ptr [ecx],edx
    L_0040b37a:
        mov edx,dword ptr [eax+4]
    L_0040b37d:
        mov dword ptr [ecx+4],edx
    L_0040b380:
        mov eax,dword ptr [eax+8]
    L_0040b383:
        mov dword ptr [ecx+8],eax
    L_0040b386:
        ret
    }
}
