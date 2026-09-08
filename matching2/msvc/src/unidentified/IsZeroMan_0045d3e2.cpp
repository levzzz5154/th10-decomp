#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D3E2..0x0045D3FA: __IsZeroMan
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_IsZeroMan_0045d3e2() {
    __asm {
    L_0045d3e2:
        xor eax,eax
    L_0045d3e4:
        mov ecx,dword ptr [esp+4]
    L_0045d3e8:
        cmp dword ptr [ecx+eax*4],0
    L_0045d3ec:
        jne short L_0045d3f8
    L_0045d3ee:
        inc eax
    L_0045d3ef:
        cmp eax,3
    L_0045d3f2:
        jl short L_0045d3e4
    L_0045d3f4:
        xor eax,eax
    L_0045d3f6:
        inc eax
    L_0045d3f7:
        ret
    L_0045d3f8:
        xor eax,eax
    L_0045d3fa:
        ret
    }
}
