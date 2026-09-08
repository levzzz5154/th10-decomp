#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448FB0..0x0044900E: FUN_00448fb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448fb0_00448fb0() {
    __asm {
    L_00448fb0:
        push ebx
    L_00448fb1:
        push ebp
    L_00448fb2:
        mov ebp,dword ptr [esp+10h]
    L_00448fb6:
        push esi
    L_00448fb7:
        mov esi,dword ptr [data_00491c10]
    L_00448fbd:
        call asm_FUN_00449950_00449950
    L_00448fc2:
        mov ebx,dword ptr [esp+18h]
    L_00448fc6:
        mov esi,eax
    L_00448fc8:
        or dword ptr [esi+35Ch],40000000h
    L_00448fd2:
        mov dword ptr [esi+20h],0
    L_00448fd9:
        mov ecx,dword ptr [edi]
    L_00448fdb:
        lea eax,[esi+340h]
    L_00448fe1:
        mov dword ptr [eax],ecx
    L_00448fe3:
        mov edx,dword ptr [edi+4]
    L_00448fe6:
        mov dword ptr [eax+4],edx
    L_00448fe9:
        mov ecx,dword ptr [edi+8]
    L_00448fec:
        mov dword ptr [eax+8],ecx
    L_00448fef:
        mov ecx,dword ptr [esp+10h]
    L_00448ff3:
        mov eax,esi
    L_00448ff5:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448ffa:
        mov edx,dword ptr [data_00491c10]
    L_00449000:
        mov ebx,esi
    L_00449002:
        mov eax,ebp
    L_00449004:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00449009:
        pop esi
    L_0044900a:
        pop ebp
    L_0044900b:
        pop ebx
    L_0044900c:
        ret 0Ch
    }
}
