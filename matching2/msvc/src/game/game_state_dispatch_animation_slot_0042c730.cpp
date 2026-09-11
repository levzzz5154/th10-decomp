#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0042C730..0x0042C74A: ?GameState_DispatchAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlot_0042c730() {
    __asm {
    L_0042c730:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c737:
        push edi
    L_0042c738:
        push edx
    L_0042c739:
        mov edx,dword ptr [data_00491c10]
    L_0042c73f:
        mov edi,2
    L_0042c744:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c749:
        pop edi
    L_0042c74a:
        ret
    }
}
