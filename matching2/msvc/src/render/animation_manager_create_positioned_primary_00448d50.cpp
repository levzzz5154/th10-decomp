#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448D50..0x00448DAE: ?AnimationManager_CreatePositionedPrimary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreatePositionedPrimary_00448d50() {
    __asm {
    L_00448d50:
        push ebx
    L_00448d51:
        push ebp
    L_00448d52:
        mov ebp,dword ptr [esp+10h]
    L_00448d56:
        push esi
    L_00448d57:
        mov esi,dword ptr [data_00491c10]
    L_00448d5d:
        call asm_FUN_00449950_00449950
    L_00448d62:
        mov ebx,dword ptr [esp+18h]
    L_00448d66:
        mov esi,eax
    L_00448d68:
        or dword ptr [esi+35Ch],40000000h
    L_00448d72:
        mov dword ptr [esi+20h],0
    L_00448d79:
        mov ecx,dword ptr [edi]
    L_00448d7b:
        lea eax,[esi+340h]
    L_00448d81:
        mov dword ptr [eax],ecx
    L_00448d83:
        mov edx,dword ptr [edi+4]
    L_00448d86:
        mov dword ptr [eax+4],edx
    L_00448d89:
        mov ecx,dword ptr [edi+8]
    L_00448d8c:
        mov dword ptr [eax+8],ecx
    L_00448d8f:
        mov ecx,dword ptr [esp+10h]
    L_00448d93:
        mov eax,esi
    L_00448d95:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448d9a:
        mov edx,dword ptr [data_00491c10]
    L_00448da0:
        mov ebx,esi
    L_00448da2:
        mov eax,ebp
    L_00448da4:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448da9:
        pop esi
    L_00448daa:
        pop ebp
    L_00448dab:
        pop ebx
    L_00448dac:
        ret 0Ch
    }
}
