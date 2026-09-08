#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462FC1..0x00462FDF: AdjustPointer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AdjustPointer_00462fc1() {
    __asm {
    L_00462fc1:
        push esi
    L_00462fc2:
        mov esi,eax
    L_00462fc4:
        mov eax,dword ptr [ecx]
    L_00462fc6:
        add eax,esi
    L_00462fc8:
        cmp dword ptr [ecx+4],0
    L_00462fcc:
        jl short L_00462fde
    L_00462fce:
        mov edx,dword ptr [ecx+4]
    L_00462fd1:
        mov ecx,dword ptr [ecx+8]
    L_00462fd4:
        mov esi,dword ptr [edx+esi]
    L_00462fd7:
        mov ecx,dword ptr [esi+ecx]
    L_00462fda:
        add ecx,edx
    L_00462fdc:
        add eax,ecx
    L_00462fde:
        pop esi
    L_00462fdf:
        ret
    }
}
