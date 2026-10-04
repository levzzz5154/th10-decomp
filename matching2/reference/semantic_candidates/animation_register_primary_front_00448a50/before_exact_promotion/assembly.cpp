#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448A50..0x00448ABF: ?AnimationManager_RegisterPrimaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50() {
    __asm {
    L_00448a50:
        lea ecx,[ebx+4]
    L_00448a53:
        push esi
    L_00448a54:
        mov dword ptr [ecx],ebx
    L_00448a56:
        mov dword ptr [ecx+4],0
    L_00448a5d:
        mov dword ptr [ecx+8],0
    L_00448a64:
        mov esi,dword ptr [edx+72DAD4h]
    L_00448a6a:
        test esi,esi
    L_00448a6c:
        jne short L_00448a76
    L_00448a6e:
        mov dword ptr [edx+72DAD8h],ecx
    L_00448a74:
        jmp short L_00448a8e
    L_00448a76:
        push edi
    L_00448a77:
        mov edi,dword ptr [ecx+4]
    L_00448a7a:
        test edi,edi
    L_00448a7c:
        je short L_00448a87
    L_00448a7e:
        mov dword ptr [esi+4],edi
    L_00448a81:
        mov edi,dword ptr [ecx+4]
    L_00448a84:
        mov dword ptr [edi+8],esi
    L_00448a87:
        mov dword ptr [ecx+4],esi
    L_00448a8a:
        mov dword ptr [esi+8],ecx
    L_00448a8d:
        pop edi
    L_00448a8e:
        mov dword ptr [edx+72DAD4h],ecx
    L_00448a94:
        mov esi,dword ptr [edx+732454h]
    L_00448a9a:
        inc esi
    L_00448a9b:
        mov ecx,esi
    L_00448a9d:
        test ecx,ecx
    L_00448a9f:
        mov dword ptr [edx+732454h],esi
    L_00448aa5:
        pop esi
    L_00448aa6:
        jne short L_00448aaf
    L_00448aa8:
        inc ecx
    L_00448aa9:
        mov dword ptr [edx+732454h],ecx
    L_00448aaf:
        mov ecx,dword ptr [edx+732454h]
    L_00448ab5:
        mov dword ptr [ebx],ecx
    L_00448ab7:
        mov edx,dword ptr [edx+732454h]
    L_00448abd:
        mov dword ptr [eax],edx
    L_00448abf:
        ret
    }
}
