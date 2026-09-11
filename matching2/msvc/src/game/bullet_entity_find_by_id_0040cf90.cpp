#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040CF90..0x0040CFA5: BulletEntity_FindById
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletEntity_FindById_0040cf90() {
    __asm {
    L_0040cf90:
        mov eax,dword ptr [eax+18h]
    L_0040cf93:
        test eax,eax
    L_0040cf95:
        je short L_0040cfa3
    L_0040cf97:
        cmp dword ptr [eax+54h],ecx
    L_0040cf9a:
        je short L_0040cfa5
    L_0040cf9c:
        mov eax,dword ptr [eax+8]
    L_0040cf9f:
        test eax,eax
    L_0040cfa1:
        jne short L_0040cf97
    L_0040cfa3:
        xor eax,eax
    L_0040cfa5:
        ret
    }
}
