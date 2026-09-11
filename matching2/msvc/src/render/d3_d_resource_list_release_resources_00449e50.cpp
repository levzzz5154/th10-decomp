#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438880..0x004388E6: ?D3DResourceManager_Destroy@@
// Naked body preserves the retail register/stack ABI.

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
