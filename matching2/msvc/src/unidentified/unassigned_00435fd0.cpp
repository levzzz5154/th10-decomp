#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435FD0..0x00435FF9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00435fd0() {
    __asm {
    L_00435fd0:
        push edi
    L_00435fd1:
        xor eax,eax
    L_00435fd3:
        mov ecx,800h
    L_00435fd8:
        mov edi,48F868h
    L_00435fdd:
        rep stosd
    L_00435fdf:
        mov eax,47785Ch
    L_00435fe4:
        xor ecx,ecx
    L_00435fe6:
        pop edi
    L_00435fe7:
        mov dword ptr [eax-4],ecx
    L_00435fea:
        mov dword ptr [eax],ecx
    L_00435fec:
        mov dword ptr [eax+4],ecx
    L_00435fef:
        add eax,0Ch
    L_00435ff2:
        cmp eax,48F868h
    L_00435ff7:
        jl short L_00435fe7
    L_00435ff9:
        ret
    }
}
