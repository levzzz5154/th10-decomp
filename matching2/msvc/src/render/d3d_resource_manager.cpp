#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

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

// 0x00449A90..0x00449A9B: ?D3DResourceList_ClearPending@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceList_ClearPending_00449a90() {
    __asm {
    L_00449a90:
        xor ecx,ecx
    L_00449a92:
        mov dword ptr [eax+8],ecx
    L_00449a95:
        mov dword ptr [eax+0Ch],ecx
    L_00449a98:
        mov dword ptr [eax+10h],ecx
    L_00449a9b:
        ret
    }
}

// 0x00449AA0..0x00449ADA: ?D3DResourceManager_Initialize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceManager_Initialize_00449aa0() {
    __asm {
    L_00449aa0:
        mov ecx,dword ptr [eax+4]
    L_00449aa3:
        xor edx,edx
    L_00449aa5:
        mov dword ptr [eax+8],edx
    L_00449aa8:
        mov dword ptr [eax+0Ch],edx
    L_00449aab:
        mov dword ptr [eax+10h],edx
    L_00449aae:
        mov dword ptr [eax],edx
    L_00449ab0:
        and ecx,0FFFFFFFEh
    L_00449ab3:
        mov dword ptr [eax+4],ecx
    L_00449ab6:
        lea ecx,[eax+24h]
    L_00449ab9:
        mov dword ptr [eax+14h],eax
    L_00449abc:
        mov dword ptr [eax+18h],edx
    L_00449abf:
        mov dword ptr [eax+1Ch],edx
    L_00449ac2:
        and dword ptr [ecx+4],0FFFFFFFEh
    L_00449ac6:
        mov dword ptr [ecx+8],edx
    L_00449ac9:
        mov dword ptr [ecx+0Ch],edx
    L_00449acc:
        mov dword ptr [ecx+10h],edx
    L_00449acf:
        mov dword ptr [ecx],edx
    L_00449ad1:
        mov dword ptr [ecx+14h],ecx
    L_00449ad4:
        mov dword ptr [ecx+18h],edx
    L_00449ad7:
        mov dword ptr [ecx+1Ch],edx
    L_00449ada:
        ret
    }
}

// 0x00449E50..0x00449EA1: ?D3DResourceList_ReleaseResources@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceList_ReleaseResources_00449e50() {
    __asm {
    L_00449e50:
        mov eax,dword ptr [eax+18h]
    L_00449e53:
        test eax,eax
    L_00449e55:
        je short L_00449e9f
    L_00449e57:
        push ebx
    L_00449e58:
        mov ebx,dword ptr [data_004660b0]
    L_00449e5e:
        push ebp
    L_00449e5f:
        mov ebp,dword ptr [data_004660b4]
    L_00449e65:
        push esi
    L_00449e66:
        push edi
    L_00449e67:
        mov esi,dword ptr [eax]
    L_00449e69:
        test esi,esi
    L_00449e6b:
        mov edi,dword ptr [eax+4]
    L_00449e6e:
        je short L_00449e95
    L_00449e70:
        push 492274h
    L_00449e75:
        call ebx
    L_00449e77:
        inc byte ptr [data_0049231c]
    L_00449e7d:
        mov edx,dword ptr [esp+14h]
    L_00449e81:
        mov ecx,esi
    L_00449e83:
        call asm_Scheduler_Remove_00449f60
    L_00449e88:
        push 492274h
    L_00449e8d:
        call ebp
    L_00449e8f:
        dec byte ptr [data_0049231c]
    L_00449e95:
        test edi,edi
    L_00449e97:
        mov eax,edi
    L_00449e99:
        jne short L_00449e67
    L_00449e9b:
        pop edi
    L_00449e9c:
        pop esi
    L_00449e9d:
        pop ebp
    L_00449e9e:
        pop ebx
    L_00449e9f:
        ret 4
    }
}
