#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444CB0..0x00444CD1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00444cb0() {
    __asm {
    L_00444cb0:
        test ecx,ecx
    L_00444cb2:
        jle short L_00444ccf
    L_00444cb4:
        add eax,10h
    L_00444cb7:
        push esi
    L_00444cb8:
        jmp short L_00444cc0
    L_00444cba:
        lea ebx,[ebx+force_disp32_zero]
    L_00444cc0:
        mov esi,dword ptr [edx+2FCh]
    L_00444cc6:
        mov dword ptr [eax],esi
    L_00444cc8:
        add eax,1Ch
    L_00444ccb:
        dec ecx
    L_00444ccc:
        jne short L_00444cc0
    L_00444cce:
        pop esi
    L_00444ccf:
        xor eax,eax
    L_00444cd1:
        ret
    }
}
