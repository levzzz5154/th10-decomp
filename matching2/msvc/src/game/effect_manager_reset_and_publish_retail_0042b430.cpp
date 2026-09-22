// BLOCKED (D3605): closest_byte_count=6/134; first_diff=0x0042B430.
// residual_class=private EBX receiver plus compiler-sensitive REP STOSD
// clearing of two large regions, callee-saved ESI/EDI state, and fixed
// global publication. variants_tested=live Ghidra decompilation and a typed
// cdecl pointer/loop candidate under MSVC 13.10 (237-byte extent, 6/134
// same-position bytes); exact naked baseline probe=134/134. next_lever=
// native-LTCG cluster with the real 0x0042B6F0 caller and an EBX-pinned
// EffectManager layout so the two REP STOSD loops and RET ABI are visible.
// 0x0042B430..0x0042B4B5: EffectManager_ResetAndPublishRetail
#include "asm_symbols.hpp"

// 0x0042B430..0x0042B4B5: EffectManager_ResetAndPublishRetail
// Naked body preserves the retail register/stack ABI.

// 0x0042B430..0x0042B4B5: EffectManager_ResetAndPublishRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectManager_ResetAndPublishRetail_0042b430() {
    __asm {
    L_0042b430:
        lea edx,[ebx+18h]
    L_0042b433:
        push esi
    L_0042b434:
        push edi
    L_0042b435:
        mov edi,dword ptr [edx+6Ch]
    L_0042b438:
        mov esi,0FFFFFFFEh
    L_0042b43d:
        and edi,esi
    L_0042b43f:
        mov dword ptr [edx+6Ch],edi
    L_0042b442:
        and dword ptr [edx+0B0h],esi
    L_0042b448:
        and dword ptr [edx+0FCh],esi
    L_0042b44e:
        and dword ptr [edx+128h],esi
    L_0042b454:
        and dword ptr [edx+174h],esi
    L_0042b45a:
        and dword ptr [edx+1B0h],esi
    L_0042b460:
        and dword ptr [edx+1FCh],esi
    L_0042b466:
        and dword ptr [edx+228h],esi
    L_0042b46c:
        and dword ptr [edx+378h],esi
    L_0042b472:
        xor eax,eax
    L_0042b474:
        mov ecx,0EBh
    L_0042b479:
        mov edi,edx
    L_0042b47b:
        rep stosd
    L_0042b47d:
        mov word ptr [edx+384h],0FFFFh
    L_0042b486:
        lea eax,[ebx+3F0h]
    L_0042b48c:
        mov ecx,2D3h
    L_0042b491:
        and dword ptr [eax],esi
    L_0042b493:
        add eax,40h
    L_0042b496:
        dec ecx
    L_0042b497:
        jne short L_0042b491
    L_0042b499:
        xor eax,eax
    L_0042b49b:
        mov ecx,2E21h
    L_0042b4a0:
        mov edi,ebx
    L_0042b4a2:
        rep stosd
    L_0042b4a4:
        mov eax,dword ptr [ebx]
    L_0042b4a6:
        or eax,2
    L_0042b4a9:
        pop edi
    L_0042b4aa:
        mov dword ptr [ebx],eax
    L_0042b4ac:
        mov dword ptr [data_00477840],ebx
    L_0042b4b2:
        mov eax,ebx
    L_0042b4b4:
        pop esi
    L_0042b4b5:
        ret
    }
}
