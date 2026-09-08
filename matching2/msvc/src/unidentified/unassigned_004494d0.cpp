#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004494D0..0x0044950E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004494d0() {
    __asm {
    L_004494d0:
        mov ecx,dword ptr [eax]
    L_004494d2:
        mov edx,dword ptr [data_00491c10]
    L_004494d8:
        push ecx
    L_004494d9:
        call asm_AnimationManager_Find_004491c0
    L_004494de:
        test eax,eax
    L_004494e0:
        TH10_REL8(0x74, 0x004494e0, VA_asm_target_00449528)
    L_004494e2:
        mov ecx,dword ptr [eax+35Ch]
    L_004494e8:
        and ecx,0FFFFFFFDh
    L_004494eb:
        mov edx,20000h
    L_004494f0:
        or ecx,edx
    L_004494f2:
        mov dword ptr [eax+35Ch],ecx
    L_004494f8:
        mov ecx,dword ptr [eax+18h]
    L_004494fb:
        test ecx,ecx
    L_004494fd:
        TH10_REL8(0x75, 0x004494fd, VA_asm_target_00449528)
    L_004494ff:
        mov eax,dword ptr [eax+14h]
    L_00449502:
        test eax,eax
    L_00449504:
        TH10_REL8(0x74, 0x00449504, VA_asm_target_00449528)
    L_00449506:
        TH10_REL8(0xeb, 0x00449506, VA_asm_unassigned_00449510)
    L_00449508:
        lea esp,[esp+force_disp32_zero]
    }
}
