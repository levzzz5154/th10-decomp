#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449530..0x0044958B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449530() {
    __asm {
    L_00449530:
        mov ecx,dword ptr [eax]
    L_00449532:
        mov edx,dword ptr [data_00491c10]
    L_00449538:
        push ecx
    L_00449539:
        call asm_AnimationManager_Find_004491c0
    L_0044953e:
        test eax,eax
    L_00449540:
        je short L_0044958b
    L_00449542:
        mov ecx,dword ptr [eax+35Ch]
    L_00449548:
        and ecx,0FFFDFFFFh
    L_0044954e:
        mov edx,2
    L_00449553:
        or ecx,edx
    L_00449555:
        mov dword ptr [eax+35Ch],ecx
    L_0044955b:
        mov ecx,dword ptr [eax+18h]
    L_0044955e:
        test ecx,ecx
    L_00449560:
        jne short L_0044958b
    L_00449562:
        mov eax,dword ptr [eax+14h]
    L_00449565:
        test eax,eax
    L_00449567:
        je short L_0044958b
    L_00449569:
        lea esp,[esp+force_disp32_zero]
    L_00449570:
        mov ecx,dword ptr [eax]
    L_00449572:
        or dword ptr [ecx+35Ch],edx
    L_00449578:
        mov ecx,dword ptr [eax]
    L_0044957a:
        and dword ptr [ecx+35Ch],0FFFDFFFFh
    L_00449584:
        mov eax,dword ptr [eax+4]
    L_00449587:
        test eax,eax
    L_00449589:
        jne short L_00449570
    L_0044958b:
        ret
    }
}
