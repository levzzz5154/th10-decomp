#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0042C750..0x0042C76A: ?GameState_DispatchAnimationSlotSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlotSecondary_0042c750() {
    __asm {
    L_0042c750:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c757:
        push edi
    L_0042c758:
        push edx
    L_0042c759:
        mov edx,dword ptr [data_00491c10]
    L_0042c75f:
        mov edi,3
    L_0042c764:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c769:
        pop edi
    L_0042c76a:
        ret
    }
}
