#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040CF60..0x0040CF76: BulletEntity_SetAnimationVector
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletEntity_SetAnimationVector_0040cf60() {
    __asm {
    L_0040cf60:
        mov edx,dword ptr [eax]
    L_0040cf62:
        add ecx,430h
    L_0040cf68:
        mov dword ptr [ecx],edx
    L_0040cf6a:
        mov edx,dword ptr [eax+4]
    L_0040cf6d:
        mov dword ptr [ecx+4],edx
    L_0040cf70:
        mov eax,dword ptr [eax+8]
    L_0040cf73:
        mov dword ptr [ecx+8],eax
    L_0040cf76:
        ret
    }
}
