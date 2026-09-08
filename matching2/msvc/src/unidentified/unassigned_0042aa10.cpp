#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AA10..0x0042AA41: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042aa10() {
    __asm {
    L_0042aa10:
        xor ecx,ecx
    L_0042aa12:
        mov edx,eax
    L_0042aa14:
        mov dword ptr [edx],ecx
    L_0042aa16:
        mov dword ptr [edx+4],ecx
    L_0042aa19:
        mov dword ptr [edx+8],ecx
    L_0042aa1c:
        mov dword ptr [edx+0Ch],ecx
    L_0042aa1f:
        mov dword ptr [edx+10h],ecx
    L_0042aa22:
        mov dword ptr [edx+14h],ecx
    L_0042aa25:
        mov dword ptr [edx+18h],ecx
    L_0042aa28:
        mov dword ptr [edx+1Ch],ecx
    L_0042aa2b:
        mov dword ptr [edx+20h],ecx
    L_0042aa2e:
        mov dword ptr [eax],72303174h
    L_0042aa34:
        mov word ptr [eax+4],5
    L_0042aa3a:
        mov dword ptr [eax+10h],100h
    L_0042aa41:
        ret
    }
}
