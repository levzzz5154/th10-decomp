#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x00422C30..0x00422C79: ?GameState_Unpause@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_Unpause_00422c30() {
    __asm {
    L_00422c30:
        mov eax,dword ptr [data_00477810]
    L_00422c35:
        mov ecx,dword ptr [eax+58h]
    L_00422c38:
        and ecx,0FFFFFFEFh
    L_00422c3b:
        push 0
    L_00422c3d:
        mov dword ptr [eax+58h],ecx
    L_00422c40:
        push 7
    L_00422c42:
        mov edx,46E0B8h
    L_00422c47:
        mov eax,492590h
    L_00422c4c:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00422c51:
        mov eax,dword ptr [esi+1DCh]
    L_00422c57:
        mov edx,dword ptr [data_00491c10]
    L_00422c5d:
        push eax
    L_00422c5e:
        call asm_AnimationManager_SetFlag_004492a0
    L_00422c63:
        mov dword ptr [esi+1DCh],0
    L_00422c6d:
        mov ecx,dword ptr [esi+2C0h]
    L_00422c73:
        mov dword ptr [data_00476f78],ecx
    L_00422c79:
        ret
    }
}
