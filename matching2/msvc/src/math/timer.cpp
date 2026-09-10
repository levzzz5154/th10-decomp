#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C620..0x0042C66F: ?GameState_SetTimerTarget@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_SetTimerTarget_0042c620() {
    __asm {
    L_0042c620:
        mov dword ptr [eax+20h],ecx
    L_0042c623:
        mov ecx,dword ptr [eax+2C0h]
    L_0042c629:
        xor edx,edx
    L_0042c62b:
        test cl,1
    L_0042c62e:
        jne short L_0042c659
    L_0042c630:
        or ecx,1
    L_0042c633:
        mov dword ptr [eax+2B4h],edx
    L_0042c639:
        mov dword ptr [eax+2B0h],0FFF0BDC1h
    L_0042c643:
        mov dword ptr [eax+2B8h],edx
    L_0042c649:
        mov dword ptr [eax+2BCh],476F78h
    L_0042c653:
        mov dword ptr [eax+2C0h],ecx
    L_0042c659:
        mov dword ptr [eax+2B4h],edx
    L_0042c65f:
        mov dword ptr [eax+2B8h],edx
    L_0042c665:
        mov dword ptr [eax+2B0h],0FFFFFFFFh
    L_0042c66f:
        ret
    }
}
