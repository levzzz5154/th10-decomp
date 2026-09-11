#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040CEA0..0x0040CEC3: ?BulletEntity_MarkAnimationForRemoval@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletEntity_MarkAnimationForRemoval_0040cea0() {
    __asm {
    L_0040cea0:
        or dword ptr [esi+378Ch],10h
    L_0040cea7:
        mov eax,dword ptr [esi+774h]
    L_0040cead:
        mov edx,dword ptr [data_00491c10]
    L_0040ceb3:
        push eax
    L_0040ceb4:
        call asm_AnimationManager_SetFlag_004492a0
    L_0040ceb9:
        mov dword ptr [esi+774h],0
    L_0040cec3:
        ret
    }
}
