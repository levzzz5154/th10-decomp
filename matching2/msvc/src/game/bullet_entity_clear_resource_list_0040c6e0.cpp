#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040C6E0..0x0040C70C: BulletEntity_ClearResourceList
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletEntity_ClearResourceList_0040c6e0() {
    __asm {
    L_0040c6e0:
        push esi
    L_0040c6e1:
        mov esi,dword ptr [eax+1034h]
    L_0040c6e7:
        test esi,esi
    L_0040c6e9:
        je short L_0040c70b
    L_0040c6eb:
        push edi
    L_0040c6ec:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040c6f0:
        mov ecx,dword ptr [esi]
    L_0040c6f2:
        mov edi,dword ptr [esi+4]
    L_0040c6f5:
        push ecx
    L_0040c6f6:
        call asm_free_004524a1
    L_0040c6fb:
        push esi
    L_0040c6fc:
        call asm_free_004524a1
    L_0040c701:
        add esp,8
    L_0040c704:
        test edi,edi
    L_0040c706:
        mov esi,edi
    L_0040c708:
        jne short L_0040c6f0
    L_0040c70a:
        pop edi
    L_0040c70b:
        pop esi
    L_0040c70c:
        ret
    }
}
