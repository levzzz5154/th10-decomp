#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0042AE60..0x0042AEE3: EffectManager_InitializePoolsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectManager_InitializePoolsRetail_0042ae60() {
    __asm {
    L_0042ae60:
        push ecx
    L_0042ae61:
        push ebx
    L_0042ae62:
        push esi
    L_0042ae63:
        mov ebx,eax
    L_0042ae65:
        push edi
    L_0042ae66:
        xor eax,eax
    L_0042ae68:
        mov ecx,772Dh
    L_0042ae6d:
        mov edi,ebx
    L_0042ae6f:
        rep stosd
    L_0042ae71:
        push 1
    L_0042ae73:
        lea eax,[esp+10h]
    L_0042ae77:
        push eax
    L_0042ae78:
        mov eax,46E848h
    L_0042ae7d:
        call asm_FUN_0044b360_0044b360
    L_0042ae82:
        lea edx,[ebx+1D86Ch]
    L_0042ae88:
        mov dword ptr [ebx],eax
    L_0042ae8a:
        call asm_Recovery_InitializeRandomTable_0042add0
    L_0042ae8f:
        lea esi,[ebx+8]
    L_0042ae92:
        mov ecx,esi
    L_0042ae94:
        sub ecx,ebx
    L_0042ae96:
        lea edi,[ecx-8]
    L_0042ae99:
        mov eax,79641CB1h
    L_0042ae9e:
        imul edi
    L_0042aea0:
        sar edx,0Dh
    L_0042aea3:
        mov eax,edx
    L_0042aea5:
        shr eax,1Fh
    L_0042aea8:
        add eax,edx
    L_0042aeaa:
        cmp eax,7
    L_0042aead:
        jae short L_0042aed8
    L_0042aeaf:
        nop
    L_0042aeb0:
        push esi
    L_0042aeb1:
        call asm_ScoreFile_InitializeDefaultsRetail_0042acb0
    L_0042aeb6:
        add edi,437Ch
    L_0042aebc:
        mov eax,79641CB1h
    L_0042aec1:
        imul edi
    L_0042aec3:
        sar edx,0Dh
    L_0042aec6:
        mov ecx,edx
    L_0042aec8:
        shr ecx,1Fh
    L_0042aecb:
        add ecx,edx
    L_0042aecd:
        add esi,437Ch
    L_0042aed3:
        cmp ecx,7
    L_0042aed6:
        jb short L_0042aeb0
    L_0042aed8:
        call asm_FUN_0042b030_0042b030
    L_0042aedd:
        pop edi
    L_0042aede:
        pop esi
    L_0042aedf:
        mov eax,ebx
    L_0042aee1:
        pop ebx
    L_0042aee2:
        pop ecx
    L_0042aee3:
        ret
    }
}
