#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040D680..0x0040D6A3: BulletEntity_ReleaseResource
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletEntity_ReleaseResource_0040d680() {
    __asm {
    L_0040d680:
        mov eax,dword ptr [esi+8Ch]
    L_0040d686:
        test eax,eax
    L_0040d688:
        mov dword ptr [esi],46D0F0h
    L_0040d68e:
        je short L_0040d6a3
    L_0040d690:
        push eax
    L_0040d691:
        call asm_free_00452422
    L_0040d696:
        add esp,4
    L_0040d699:
        mov dword ptr [esi+8Ch],0
    L_0040d6a3:
        ret
    }
}
