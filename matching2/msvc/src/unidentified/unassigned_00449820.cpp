#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449820..0x00449859: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449820() {
    __asm {
    L_00449820:
        mov eax,dword ptr [esi]
    L_00449822:
        mov edx,dword ptr [data_00491c10]
    L_00449828:
        push eax
    L_00449829:
        call asm_AnimationManager_Find_004491c0
    L_0044982e:
        test eax,eax
    L_00449830:
        jne short L_00449834
    L_00449832:
        mov dword ptr [esi],eax
    L_00449834:
        add eax,10h
    L_00449837:
        je short L_00449854
    L_00449839:
        lea esp,[esp+force_disp32_zero]
    L_00449840:
        mov ecx,dword ptr [eax]
    L_00449842:
        movsx edx,word ptr [ecx+38Ah]
    L_00449849:
        cmp edx,edi
    L_0044984b:
        je short L_00449857
    L_0044984d:
        mov eax,dword ptr [eax+4]
    L_00449850:
        test eax,eax
    L_00449852:
        jne short L_00449840
    L_00449854:
        xor eax,eax
    L_00449856:
        ret
    L_00449857:
        mov eax,dword ptr [eax]
    L_00449859:
        ret
    }
}
