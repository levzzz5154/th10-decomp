#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448B40..0x00448BAF: ?AnimationManager_RegisterSecondaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterSecondaryFront_00448b40() {
    __asm {
    L_00448b40:
        lea ecx,[ebx+4]
    L_00448b43:
        push esi
    L_00448b44:
        mov dword ptr [ecx],ebx
    L_00448b46:
        mov dword ptr [ecx+4],0
    L_00448b4d:
        mov dword ptr [ecx+8],0
    L_00448b54:
        mov esi,dword ptr [edx+72DADCh]
    L_00448b5a:
        test esi,esi
    L_00448b5c:
        jne short L_00448b66
    L_00448b5e:
        mov dword ptr [edx+72DAE0h],ecx
    L_00448b64:
        jmp short L_00448b7e
    L_00448b66:
        push edi
    L_00448b67:
        mov edi,dword ptr [ecx+4]
    L_00448b6a:
        test edi,edi
    L_00448b6c:
        je short L_00448b77
    L_00448b6e:
        mov dword ptr [esi+4],edi
    L_00448b71:
        mov edi,dword ptr [ecx+4]
    L_00448b74:
        mov dword ptr [edi+8],esi
    L_00448b77:
        mov dword ptr [ecx+4],esi
    L_00448b7a:
        mov dword ptr [esi+8],ecx
    L_00448b7d:
        pop edi
    L_00448b7e:
        mov dword ptr [edx+72DADCh],ecx
    L_00448b84:
        mov esi,dword ptr [edx+732454h]
    L_00448b8a:
        inc esi
    L_00448b8b:
        mov ecx,esi
    L_00448b8d:
        test ecx,ecx
    L_00448b8f:
        mov dword ptr [edx+732454h],esi
    L_00448b95:
        pop esi
    L_00448b96:
        jne short L_00448b9f
    L_00448b98:
        inc ecx
    L_00448b99:
        mov dword ptr [edx+732454h],ecx
    L_00448b9f:
        mov ecx,dword ptr [edx+732454h]
    L_00448ba5:
        mov dword ptr [ebx],ecx
    L_00448ba7:
        mov edx,dword ptr [edx+732454h]
    L_00448bad:
        mov dword ptr [eax],edx
    L_00448baf:
        ret
    }
}
