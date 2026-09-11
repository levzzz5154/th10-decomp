#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448F60..0x00448FA8: ?AnimationManager_CreateSecondaryBack@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreateSecondaryBack_00448f60() {
    __asm {
    L_00448f60:
        push ebx
    L_00448f61:
        push esi
    L_00448f62:
        mov esi,dword ptr [data_00491c10]
    L_00448f68:
        call asm_FUN_00449950_00449950
    L_00448f6d:
        mov ecx,dword ptr [esp+10h]
    L_00448f71:
        mov ebx,eax
    L_00448f73:
        mov esi,dword ptr [ebx+35Ch]
    L_00448f79:
        mov eax,dword ptr [esp+14h]
    L_00448f7d:
        push ecx
    L_00448f7e:
        mov ecx,dword ptr [esp+10h]
    L_00448f82:
        or esi,40000000h
    L_00448f88:
        push ebx
    L_00448f89:
        mov dword ptr [ebx+20h],eax
    L_00448f8c:
        mov dword ptr [ebx+35Ch],esi
    L_00448f92:
        call asm_FUN_00449870_00449870
    L_00448f97:
        mov edx,dword ptr [data_00491c10]
    L_00448f9d:
        mov eax,edi
    L_00448f9f:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00448fa4:
        pop esi
    L_00448fa5:
        pop ebx
    L_00448fa6:
        ret 0Ch
    }
}
