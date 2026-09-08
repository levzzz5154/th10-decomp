#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004535BD..0x004535EC: __endthreadex
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_endthreadex_004535bd() {
    __asm {
    L_004535bd:
        mov eax,dword ptr [data_004733b0]
    L_004535c2:
        test eax,eax
    L_004535c4:
        je short L_004535c8
    L_004535c6:
        call eax
    L_004535c8:
        push esi
    L_004535c9:
        call asm_getptd_00456357
    L_004535ce:
        mov esi,eax
    L_004535d0:
        test esi,esi
    L_004535d2:
        jne short L_004535dc
    L_004535d4:
        push 10h
    L_004535d6:
        call asm_amsg_exit_0045373d
    L_004535db:
        pop ecx
    L_004535dc:
        push esi
    L_004535dd:
        call asm_freeptd_0045650f
    L_004535e2:
        pop ecx
    L_004535e3:
        push dword ptr [esp+8]
    L_004535e7:
        call dword ptr [data_004661ac]
    }
}
