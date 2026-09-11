#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004489D0..0x00448A45: ?AnimationManager_RegisterPrimaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0() {
    __asm {
    L_004489d0:
        lea ecx,[ebx+4]
    L_004489d3:
        push esi
    L_004489d4:
        mov dword ptr [ecx],ebx
    L_004489d6:
        mov dword ptr [ecx+4],0
    L_004489dd:
        mov dword ptr [ecx+8],0
    L_004489e4:
        mov esi,dword ptr [edx+72DAD4h]
    L_004489ea:
        test esi,esi
    L_004489ec:
        jne short L_004489f6
    L_004489ee:
        mov dword ptr [edx+72DAD4h],ecx
    L_004489f4:
        jmp short L_00448a14
    L_004489f6:
        mov esi,dword ptr [edx+72DAD8h]
    L_004489fc:
        push edi
    L_004489fd:
        mov edi,dword ptr [esi+4]
    L_00448a00:
        test edi,edi
    L_00448a02:
        je short L_00448a0d
    L_00448a04:
        mov dword ptr [ecx+4],edi
    L_00448a07:
        mov edi,dword ptr [esi+4]
    L_00448a0a:
        mov dword ptr [edi+8],ecx
    L_00448a0d:
        mov dword ptr [esi+4],ecx
    L_00448a10:
        mov dword ptr [ecx+8],esi
    L_00448a13:
        pop edi
    L_00448a14:
        mov dword ptr [edx+72DAD8h],ecx
    L_00448a1a:
        mov esi,dword ptr [edx+732454h]
    L_00448a20:
        inc esi
    L_00448a21:
        mov ecx,esi
    L_00448a23:
        test ecx,ecx
    L_00448a25:
        mov dword ptr [edx+732454h],esi
    L_00448a2b:
        pop esi
    L_00448a2c:
        jne short L_00448a35
    L_00448a2e:
        inc ecx
    L_00448a2f:
        mov dword ptr [edx+732454h],ecx
    L_00448a35:
        mov ecx,dword ptr [edx+732454h]
    L_00448a3b:
        mov dword ptr [ebx],ecx
    L_00448a3d:
        mov edx,dword ptr [edx+732454h]
    L_00448a43:
        mov dword ptr [eax],edx
    L_00448a45:
        ret
    }
}
