#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D3BB..0x0045D3D5: __CopyMan
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CopyMan_0045d3bb() {
    __asm {
    L_0045d3bb:
        mov eax,dword ptr [esp+8]
    L_0045d3bf:
        mov ecx,dword ptr [esp+4]
    L_0045d3c3:
        push 3
    L_0045d3c5:
        pop edx
    L_0045d3c6:
        sub ecx,eax
    L_0045d3c8:
        push esi
    L_0045d3c9:
        mov esi,dword ptr [eax]
    L_0045d3cb:
        mov dword ptr [ecx+eax],esi
    L_0045d3ce:
        add eax,4
    L_0045d3d1:
        dec edx
    L_0045d3d2:
        jne short L_0045d3c9
    L_0045d3d4:
        pop esi
    L_0045d3d5:
        ret
    }
}
