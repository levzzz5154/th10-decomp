#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427D30..0x00427D41: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427d30() {
    __asm {
    L_00427d30:
        cmp dword ptr [ecx],eax
    L_00427d32:
        jne short L_00427d3c
    L_00427d34:
        cmp dword ptr [ecx+4],eax
    L_00427d37:
        jne short L_00427d3c
    L_00427d39:
        xor eax,eax
    L_00427d3b:
        ret
    L_00427d3c:
        mov eax,1
    L_00427d41:
        ret
    }
}
