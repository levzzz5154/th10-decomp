#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438880..0x004388E6: ?D3DResourceManager_Destroy@@
// Naked body preserves the retail register/stack ABI.

// 0x00438880..0x004388E6: ?D3DResourceManager_Destroy@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceManager_Destroy_00438880() {
    __asm {
    L_00438880:
        mov eax,dword ptr fs:[0]
    L_00438886:
        push 0FFFFFFFFh
    L_00438888:
        push 465363h
    L_0043888d:
        push eax
    L_0043888e:
        mov dword ptr fs:[0],esp
    L_00438895:
        push esi
    L_00438896:
        push edi
    L_00438897:
        mov edi,dword ptr [esp+18h]
    L_0043889b:
        mov esi,492254h
    L_004388a0:
        mov dword ptr [esp+10h],1
    L_004388a8:
        call asm_Platform_StopWorker_0044c150
    L_004388ad:
        push edi
    L_004388ae:
        mov eax,edi
    L_004388b0:
        call asm_D3DResourceList_ReleaseResources_00449e50
    L_004388b5:
        lea esi,[edi+24h]
    L_004388b8:
        push edi
    L_004388b9:
        mov eax,esi
    L_004388bb:
        call asm_D3DResourceList_ReleaseResources_00449e50
    L_004388c0:
        mov ecx,dword ptr [esp+8]
    L_004388c4:
        xor eax,eax
    L_004388c6:
        mov dword ptr [esi+8],eax
    L_004388c9:
        mov dword ptr [esi+0Ch],eax
    L_004388cc:
        mov dword ptr [esi+10h],eax
    L_004388cf:
        mov dword ptr [edi+8],eax
    L_004388d2:
        mov dword ptr [edi+0Ch],eax
    L_004388d5:
        mov dword ptr [edi+10h],eax
    L_004388d8:
        pop edi
    L_004388d9:
        mov dword ptr fs:[0],ecx
    L_004388e0:
        pop esi
    L_004388e1:
        add esp,0Ch
    L_004388e4:
        ret 4
    }
}
