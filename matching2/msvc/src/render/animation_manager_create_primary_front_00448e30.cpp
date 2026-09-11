#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448E30..0x00448E78: ?AnimationManager_CreatePrimaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePrimaryFront_00448e30() {
    __asm {
    L_00448e30:
        push ebx
    L_00448e31:
        push esi
    L_00448e32:
        mov esi,dword ptr [data_00491c10]
    L_00448e38:
        call asm_FUN_00449950_00449950
    L_00448e3d:
        mov ecx,dword ptr [esp+10h]
    L_00448e41:
        mov ebx,eax
    L_00448e43:
        mov esi,dword ptr [ebx+35Ch]
    L_00448e49:
        mov eax,dword ptr [esp+14h]
    L_00448e4d:
        push ecx
    L_00448e4e:
        mov ecx,dword ptr [esp+10h]
    L_00448e52:
        or esi,40000000h
    L_00448e58:
        push ebx
    L_00448e59:
        mov dword ptr [ebx+20h],eax
    L_00448e5c:
        mov dword ptr [ebx+35Ch],esi
    L_00448e62:
        call asm_FUN_00449870_00449870
    L_00448e67:
        mov edx,dword ptr [data_00491c10]
    L_00448e6d:
        mov eax,edi
    L_00448e6f:
        call asm_AnimationManager_RegisterPrimaryFront_00448a50
    L_00448e74:
        pop esi
    L_00448e75:
        pop ebx
    L_00448e76:
        ret 0Ch
    }
}
