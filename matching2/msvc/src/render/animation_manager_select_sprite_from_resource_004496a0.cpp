#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004496A0..0x004496C1: ?AnimationManager_SelectSpriteFromResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SelectSpriteFromResource_004496a0() {
    __asm {
    L_004496a0:
        mov ecx,dword ptr [eax]
    L_004496a2:
        mov edx,dword ptr [data_00491c10]
    L_004496a8:
        push ecx
    L_004496a9:
        call asm_AnimationManager_Find_004491c0
    L_004496ae:
        test eax,eax
    L_004496b0:
        je short L_004496bf
    L_004496b2:
        mov edx,dword ptr [esp+8]
    L_004496b6:
        mov ecx,dword ptr [esp+4]
    L_004496ba:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004496bf:
        ret 8
    }
}
