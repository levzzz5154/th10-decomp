#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424530..0x00424583: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424530() {
    __asm {
    L_00424530:
        mov ecx,dword ptr [eax+4]
    L_00424533:
        test ecx,ecx
    L_00424535:
        jl short L_0042453d
    L_00424537:
        or eax,0FFFFFFFFh
    L_0042453a:
        ret 24h
    L_0042453d:
        mov ecx,dword ptr [esp+4]
    L_00424541:
        mov dword ptr [eax+4],ecx
    L_00424544:
        mov ecx,dword ptr [esp+0Ch]
    L_00424548:
        mov dword ptr [eax+8],edx
    L_0042454b:
        mov edx,dword ptr [esp+10h]
    L_0042454f:
        mov dword ptr [eax+0Ch],ecx
    L_00424552:
        mov ecx,dword ptr [esp+14h]
    L_00424556:
        mov dword ptr [eax+10h],edx
    L_00424559:
        mov edx,dword ptr [esp+18h]
    L_0042455d:
        mov dword ptr [eax+14h],ecx
    L_00424560:
        mov ecx,dword ptr [esp+1Ch]
    L_00424564:
        mov dword ptr [eax+18h],edx
    L_00424567:
        mov edx,dword ptr [esp+20h]
    L_0042456b:
        mov dword ptr [eax+1Ch],ecx
    L_0042456e:
        mov ecx,dword ptr [esp+24h]
    L_00424572:
        mov dword ptr [eax+20h],edx
    L_00424575:
        mov edx,dword ptr [esp+8]
    L_00424579:
        mov dword ptr [eax+24h],ecx
    L_0042457c:
        mov dword ptr [eax+28h],edx
    L_0042457f:
        xor eax,eax
    L_00424581:
        ret 24h
    }
}
