#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004477D0..0x00447806: ?AnimationManager_ClearResourceSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ClearResourceSlot_004477d0() {
    __asm {
    L_004477d0:
        test esi,esi
    L_004477d2:
        jl short L_00447806
    L_004477d4:
        cmp esi,21h
    L_004477d7:
        jae short L_00447806
    L_004477d9:
        push edi
    L_004477da:
        mov edi,dword ptr [ebx+esi*4+3AD06Ch]
    L_004477e1:
        test edi,edi
    L_004477e3:
        je short L_00447805
    L_004477e5:
        call asm_FUN_00447810_00447810
    L_004477ea:
        mov eax,dword ptr [ebx+esi*4+3AD06Ch]
    L_004477f1:
        push eax
    L_004477f2:
        call asm_free_004524a1
    L_004477f7:
        add esp,4
    L_004477fa:
        mov dword ptr [ebx+esi*4+3AD06Ch],0
    L_00447805:
        pop edi
    L_00447806:
        ret
    }
}
