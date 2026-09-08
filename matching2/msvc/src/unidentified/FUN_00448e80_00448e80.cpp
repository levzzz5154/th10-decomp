#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448E80..0x00448EDE: FUN_00448e80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448e80_00448e80() {
    __asm {
    L_00448e80:
        push ebx
    L_00448e81:
        push ebp
    L_00448e82:
        mov ebp,dword ptr [esp+10h]
    L_00448e86:
        push esi
    L_00448e87:
        mov esi,dword ptr [data_00491c10]
    L_00448e8d:
        call asm_FUN_00449950_00449950
    L_00448e92:
        mov ebx,dword ptr [esp+18h]
    L_00448e96:
        mov esi,eax
    L_00448e98:
        or dword ptr [esi+35Ch],40000000h
    L_00448ea2:
        mov dword ptr [esi+20h],0
    L_00448ea9:
        mov ecx,dword ptr [edi]
    L_00448eab:
        lea eax,[esi+340h]
    L_00448eb1:
        mov dword ptr [eax],ecx
    L_00448eb3:
        mov edx,dword ptr [edi+4]
    L_00448eb6:
        mov dword ptr [eax+4],edx
    L_00448eb9:
        mov ecx,dword ptr [edi+8]
    L_00448ebc:
        mov dword ptr [eax+8],ecx
    L_00448ebf:
        mov ecx,dword ptr [esp+10h]
    L_00448ec3:
        mov eax,esi
    L_00448ec5:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448eca:
        mov edx,dword ptr [data_00491c10]
    L_00448ed0:
        mov ebx,esi
    L_00448ed2:
        mov eax,ebp
    L_00448ed4:
        call asm_AnimationManager_RegisterPrimaryFront_00448a50
    L_00448ed9:
        pop esi
    L_00448eda:
        pop ebp
    L_00448edb:
        pop ebx
    L_00448edc:
        ret 0Ch
    }
}
