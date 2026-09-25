#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D3D6..0x0045D3E1: FUN_0045d3d6
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d3d6_0045d3d6() {
    __asm {
    L_0045d3d6:
        push edi
    L_0045d3d7:
        mov edi,dword ptr [esp+8]
    L_0045d3db:
        xor eax,eax
    L_0045d3dd:
        stosd
    L_0045d3de:
        stosd
    L_0045d3df:
        stosd
    L_0045d3e0:
        pop edi
    L_0045d3e1:
        ret
    }
}
