#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447790..0x004477CD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00447790() {
    __asm {
    L_00447790:
        xor edx,edx
    L_00447792:
        add ecx,3AD06Ch
    L_00447798:
        push esi
    L_00447799:
        lea esp,[esp+force_disp32_zero]
    L_004477a0:
        mov eax,dword ptr [ecx]
    L_004477a2:
        test eax,eax
    L_004477a4:
        je short L_004477ba
    L_004477a6:
        mov esi,dword ptr [eax+128h]
    L_004477ac:
        test esi,esi
    L_004477ae:
        jne short L_004477ca
    L_004477b0:
        mov esi,dword ptr [eax+124h]
    L_004477b6:
        test esi,esi
    L_004477b8:
        jne short L_004477ca
    L_004477ba:
        inc edx
    L_004477bb:
        add ecx,4
    L_004477be:
        cmp edx,21h
    L_004477c1:
        jb short L_004477a0
    L_004477c3:
        mov eax,1
    L_004477c8:
        pop esi
    L_004477c9:
        ret
    L_004477ca:
        xor eax,eax
    L_004477cc:
        pop esi
    L_004477cd:
        ret
    }
}
