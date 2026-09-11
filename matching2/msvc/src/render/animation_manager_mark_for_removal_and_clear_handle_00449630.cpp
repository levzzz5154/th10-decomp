#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449630..0x00449644: ?AnimationManager_MarkForRemovalAndClearHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkForRemovalAndClearHandle_00449630() {
    __asm {
    L_00449630:
        mov eax,dword ptr [esi]
    L_00449632:
        mov edx,dword ptr [data_00491c10]
    L_00449638:
        push eax
    L_00449639:
        call asm_AnimationManager_SetFlag_004492a0
    L_0044963e:
        mov dword ptr [esi],0
    L_00449644:
        ret
    }
}
