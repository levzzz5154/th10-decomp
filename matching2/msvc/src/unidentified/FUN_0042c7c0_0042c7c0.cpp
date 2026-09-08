#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C7C0..0x0042C7D8: FUN_0042c7c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c7c0_0042c7c0() {
    __asm {
    L_0042c7c0:
        push esi
    L_0042c7c1:
        push edi
    L_0042c7c2:
        mov edi,dword ptr [esp+0Ch]
    L_0042c7c6:
        lea esi,[eax+ecx*4+2C4h]
    L_0042c7cd:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0042c7d2:
        mov eax,edi
    L_0042c7d4:
        pop edi
    L_0042c7d5:
        pop esi
    L_0042c7d6:
        ret 4
    }
}
