#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448D00..0x00448D48: ?AnimationManager_CreatePrimaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePrimaryBack_00448d00() {
    __asm {
    L_00448d00:
        push ebx
    L_00448d01:
        push esi
    L_00448d02:
        mov esi,dword ptr [data_00491c10]
    L_00448d08:
        call asm_FUN_00449950_00449950
    L_00448d0d:
        mov ecx,dword ptr [esp+10h]
    L_00448d11:
        mov ebx,eax
    L_00448d13:
        mov esi,dword ptr [ebx+35Ch]
    L_00448d19:
        mov eax,dword ptr [esp+14h]
    L_00448d1d:
        push ecx
    L_00448d1e:
        mov ecx,dword ptr [esp+10h]
    L_00448d22:
        or esi,40000000h
    L_00448d28:
        push ebx
    L_00448d29:
        mov dword ptr [ebx+20h],eax
    L_00448d2c:
        mov dword ptr [ebx+35Ch],esi
    L_00448d32:
        call asm_FUN_00449870_00449870
    L_00448d37:
        mov edx,dword ptr [data_00491c10]
    L_00448d3d:
        mov eax,edi
    L_00448d3f:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448d44:
        pop esi
    L_00448d45:
        pop ebx
    L_00448d46:
        ret 0Ch
    }
}
