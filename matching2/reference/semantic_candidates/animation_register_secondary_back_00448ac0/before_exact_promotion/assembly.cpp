#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448AC0..0x00448B35: ?AnimationManager_RegisterSecondaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterSecondaryBack_00448ac0() {
    __asm {
    L_00448ac0:
        lea ecx,[ebx+4]
    L_00448ac3:
        push esi
    L_00448ac4:
        mov dword ptr [ecx],ebx
    L_00448ac6:
        mov dword ptr [ecx+4],0
    L_00448acd:
        mov dword ptr [ecx+8],0
    L_00448ad4:
        mov esi,dword ptr [edx+72DADCh]
    L_00448ada:
        test esi,esi
    L_00448adc:
        jne short L_00448ae6
    L_00448ade:
        mov dword ptr [edx+72DADCh],ecx
    L_00448ae4:
        jmp short L_00448b04
    L_00448ae6:
        mov esi,dword ptr [edx+72DAE0h]
    L_00448aec:
        push edi
    L_00448aed:
        mov edi,dword ptr [esi+4]
    L_00448af0:
        test edi,edi
    L_00448af2:
        je short L_00448afd
    L_00448af4:
        mov dword ptr [ecx+4],edi
    L_00448af7:
        mov edi,dword ptr [esi+4]
    L_00448afa:
        mov dword ptr [edi+8],ecx
    L_00448afd:
        mov dword ptr [esi+4],ecx
    L_00448b00:
        mov dword ptr [ecx+8],esi
    L_00448b03:
        pop edi
    L_00448b04:
        mov dword ptr [edx+72DAE0h],ecx
    L_00448b0a:
        mov esi,dword ptr [edx+732454h]
    L_00448b10:
        inc esi
    L_00448b11:
        mov ecx,esi
    L_00448b13:
        test ecx,ecx
    L_00448b15:
        mov dword ptr [edx+732454h],esi
    L_00448b1b:
        pop esi
    L_00448b1c:
        jne short L_00448b25
    L_00448b1e:
        inc ecx
    L_00448b1f:
        mov dword ptr [edx+732454h],ecx
    L_00448b25:
        mov ecx,dword ptr [edx+732454h]
    L_00448b2b:
        mov dword ptr [ebx],ecx
    L_00448b2d:
        mov edx,dword ptr [edx+732454h]
    L_00448b33:
        mov dword ptr [eax],edx
    L_00448b35:
        ret
    }
}
