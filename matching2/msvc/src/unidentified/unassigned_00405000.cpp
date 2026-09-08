#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405000..0x00405013: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405000() {
    __asm {
    L_00405000:
        mov edx,dword ptr [eax]
    L_00405002:
        add ecx,24h
    L_00405005:
        mov dword ptr [ecx],edx
    L_00405007:
        mov edx,dword ptr [eax+4]
    L_0040500a:
        mov dword ptr [ecx+4],edx
    L_0040500d:
        mov eax,dword ptr [eax+8]
    L_00405010:
        mov dword ptr [ecx+8],eax
    L_00405013:
        ret
    }
}
