#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CEE0..0x0040CEF3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cee0() {
    __asm {
    L_0040cee0:
        mov edx,dword ptr [eax]
    L_0040cee2:
        add ecx,24h
    L_0040cee5:
        mov dword ptr [ecx],edx
    L_0040cee7:
        mov edx,dword ptr [eax+4]
    L_0040ceea:
        mov dword ptr [ecx+4],edx
    L_0040ceed:
        mov eax,dword ptr [eax+8]
    L_0040cef0:
        mov dword ptr [ecx+8],eax
    L_0040cef3:
        ret
    }
}
