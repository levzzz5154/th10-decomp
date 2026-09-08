#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C540..0x0040C58A: FUN_0040c540
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c540_0040c540() {
    __asm {
    L_0040c540:
        sub esp,0Ch
    L_0040c543:
        mov eax,dword ptr [esp+10h]
    L_0040c547:
        mov ecx,dword ptr [esp+14h]
    L_0040c54b:
        mov dword ptr [esp],eax
    L_0040c54e:
        mov eax,dword ptr [esi+89A4h]
    L_0040c554:
        test eax,eax
    L_0040c556:
        mov dword ptr [esp+4],ecx
    L_0040c55a:
        mov dword ptr [esp+8],0
    L_0040c562:
        jne short L_0040c585
    L_0040c564:
        mov eax,dword ptr [esi+8994h]
    L_0040c56a:
        push edi
    L_0040c56b:
        push 6
    L_0040c56d:
        lea edx,[esp+18h]
    L_0040c571:
        push edx
    L_0040c572:
        push eax
    L_0040c573:
        lea edi,[esp+10h]
    L_0040c577:
        call asm_AnimationManager_CreatePositionedPrimary_00448d50
    L_0040c57c:
        mov eax,dword ptr [eax]
    L_0040c57e:
        mov dword ptr [esi+89A4h],eax
    L_0040c584:
        pop edi
    L_0040c585:
        add esp,0Ch
    L_0040c588:
        ret 8
    }
}
