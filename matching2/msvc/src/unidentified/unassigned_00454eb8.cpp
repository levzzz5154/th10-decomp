#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454EB8..0x00454ED6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00454eb8() {
    __asm {
    L_00454eb8:
        add dword ptr [eax],4
    L_00454ebb:
        mov eax,dword ptr [eax]
    L_00454ebd:
        mov eax,dword ptr [eax-4]
    L_00454ec0:
        ret
    L_00454ec1:
        add dword ptr [eax],8
    L_00454ec4:
        mov ecx,dword ptr [eax]
    L_00454ec6:
        mov eax,dword ptr [ecx-8]
    L_00454ec9:
        mov edx,dword ptr [ecx-4]
    L_00454ecc:
        ret
    L_00454ecd:
        add dword ptr [eax],4
    L_00454ed0:
        mov eax,dword ptr [eax]
    L_00454ed2:
        mov ax,word ptr [eax-4]
    L_00454ed6:
        ret
    }
}
