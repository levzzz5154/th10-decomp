#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004367A0..0x004367C2: FUN_004367a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004367a0_004367a0() {
    __asm {
    L_004367a0:
        mov ecx,dword ptr [esp+0Ch]
    L_004367a4:
        push esi
    L_004367a5:
        mov esi,dword ptr [esp+0Ch]
    L_004367a9:
        push edi
    L_004367aa:
        mov edi,dword ptr [esp+0Ch]
    L_004367ae:
        mov eax,ecx
    L_004367b0:
        mov edx,edi
    L_004367b2:
        shr ecx,2
    L_004367b5:
        rep movsd
    L_004367b7:
        mov ecx,eax
    L_004367b9:
        and ecx,3
    L_004367bc:
        rep movsb
    L_004367be:
        pop edi
    L_004367bf:
        mov eax,edx
    L_004367c1:
        pop esi
    L_004367c2:
        ret
    }
}
