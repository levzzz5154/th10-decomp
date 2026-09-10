#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C5C0..0x0042C612: ?GameState_DisableTimerWithOwner@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DisableTimerWithOwner_0042c5c0() {
    __asm {
    L_0042c5c0:
        xor edx,edx
    L_0042c5c2:
        mov dword ptr [eax+1Ch],ecx
    L_0042c5c5:
        mov dword ptr [eax+20h],edx
    L_0042c5c8:
        mov ecx,dword ptr [eax+2C0h]
    L_0042c5ce:
        test cl,1
    L_0042c5d1:
        jne short L_0042c5fc
    L_0042c5d3:
        or ecx,1
    L_0042c5d6:
        mov dword ptr [eax+2B4h],edx
    L_0042c5dc:
        mov dword ptr [eax+2B0h],0FFF0BDC1h
    L_0042c5e6:
        mov dword ptr [eax+2B8h],edx
    L_0042c5ec:
        mov dword ptr [eax+2BCh],476F78h
    L_0042c5f6:
        mov dword ptr [eax+2C0h],ecx
    L_0042c5fc:
        mov dword ptr [eax+2B4h],edx
    L_0042c602:
        mov dword ptr [eax+2B8h],edx
    L_0042c608:
        mov dword ptr [eax+2B0h],0FFFFFFFFh
    L_0042c612:
        ret
    }
}
