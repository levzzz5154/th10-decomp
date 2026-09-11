#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449670..0x00449693: ?AnimationManager_SelectSpriteFromCurrentResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SelectSpriteFromCurrentResource_00449670() {
    __asm {
    L_00449670:
        mov ecx,dword ptr [eax]
    L_00449672:
        mov edx,dword ptr [data_00491c10]
    L_00449678:
        push ecx
    L_00449679:
        call asm_AnimationManager_Find_004491c0
    L_0044967e:
        test eax,eax
    L_00449680:
        je short L_00449691
    L_00449682:
        mov edx,dword ptr [esp+4]
    L_00449686:
        mov ecx,dword ptr [eax+308h]
    L_0044968c:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00449691:
        ret 4
    }
}
