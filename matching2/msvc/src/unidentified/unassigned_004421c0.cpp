#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004421C0..0x004421D3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004421c0() {
    __asm {
    L_004421c0:
        mov edx,dword ptr [eax]
    L_004421c2:
        add ecx,0Ch
    L_004421c5:
        mov dword ptr [ecx],edx
    L_004421c7:
        mov edx,dword ptr [eax+4]
    L_004421ca:
        mov dword ptr [ecx+4],edx
    L_004421cd:
        mov eax,dword ptr [eax+8]
    L_004421d0:
        mov dword ptr [ecx+8],eax
    L_004421d3:
        ret
    }
}
