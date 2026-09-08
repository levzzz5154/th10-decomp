#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D3D0..0x0040D3F1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d3d0() {
    __asm {
    L_0040d3d0:
        xor eax,eax
    L_0040d3d2:
        push edi
    L_0040d3d3:
        mov dword ptr [edx+1090h],eax
    L_0040d3d9:
        mov dword ptr [edx+1094h],eax
    L_0040d3df:
        mov ecx,426h
    L_0040d3e4:
        mov edi,edx
    L_0040d3e6:
        rep stosd
    L_0040d3e8:
        mov dword ptr [edx],46D0B4h
    L_0040d3ee:
        mov eax,edx
    L_0040d3f0:
        pop edi
    L_0040d3f1:
        ret
    }
}
