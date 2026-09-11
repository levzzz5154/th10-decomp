#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004050D0..0x00405101: ?EmbeddedTimer_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x0042A930..0x0042A96A: EmbeddedTimer_SetCountdownRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EmbeddedTimer_SetCountdownRetail_0042a930() {
    __asm {
    L_0042a930:
        mov ecx,dword ptr [eax+24h]
    L_0042a933:
        test cl,1
    L_0042a936:
        push esi
    L_0042a937:
        mov esi,dword ptr [esp+8]
    L_0042a93b:
        jne short L_0042a959
    L_0042a93d:
        xor edx,edx
    L_0042a93f:
        or ecx,1
    L_0042a942:
        mov dword ptr [eax+18h],edx
    L_0042a945:
        mov dword ptr [eax+14h],0FFF0BDC1h
    L_0042a94c:
        mov dword ptr [eax+1Ch],edx
    L_0042a94f:
        mov dword ptr [eax+20h],476F78h
    L_0042a956:
        mov dword ptr [eax+24h],ecx
    L_0042a959:
        fild dword ptr [esp+8]
    L_0042a95d:
        mov dword ptr [eax+18h],esi
    L_0042a960:
        dec esi
    L_0042a961:
        mov dword ptr [eax+14h],esi
    L_0042a964:
        fstp dword ptr [eax+1Ch]
    L_0042a967:
        pop esi
    L_0042a968:
        ret 4
    }
}
