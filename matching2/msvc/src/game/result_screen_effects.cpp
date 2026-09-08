#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FDD0..0x0041FEAB: FUN_0041fdd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041fdd0_0041fdd0() {
    __asm {
    L_0041fdd0:
        sub esp,0Ch
    L_0041fdd3:
        push ebp
    L_0041fdd4:
        mov ebp,dword ptr [esp+14h]
    L_0041fdd8:
        cmp dword ptr [ebp+3E4h],1
    L_0041fddf:
        push esi
    L_0041fde0:
        push edi
    L_0041fde1:
        jne short L_0041fe3a
    L_0041fde3:
        mov esi,dword ptr [data_00491c10]
    L_0041fde9:
        mov edi,dword ptr [ebp+3E0h]
    L_0041fdef:
        push ebx
    L_0041fdf0:
        call asm_FUN_00449950_00449950
    L_0041fdf5:
        mov ebx,eax
    L_0041fdf7:
        mov esi,dword ptr [ebx+35Ch]
    L_0041fdfd:
        push 0
    L_0041fdff:
        or esi,40000000h
    L_0041fe05:
        push ebx
    L_0041fe06:
        mov ecx,edi
    L_0041fe08:
        mov dword ptr [ebx+20h],0Fh
    L_0041fe0f:
        mov dword ptr [ebx+35Ch],esi
    L_0041fe15:
        call asm_FUN_00449870_00449870
    L_0041fe1a:
        mov edx,dword ptr [data_00491c10]
    L_0041fe20:
        lea eax,[esp+20h]
    L_0041fe24:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0041fe29:
        mov eax,dword ptr [esp+20h]
    L_0041fe2d:
        mov dword ptr [ebp+3DCh],eax
    L_0041fe33:
        inc dword ptr [ebp+3E4h]
    L_0041fe39:
        pop ebx
    L_0041fe3a:
        cmp dword ptr [ebp+3E8h],1
    L_0041fe41:
        jne short L_0041fe91
    L_0041fe43:
        mov eax,dword ptr [data_004776e0]
    L_0041fe48:
        mov ecx,dword ptr [eax+89A4h]
    L_0041fe4e:
        test ecx,ecx
    L_0041fe50:
        lea esi,[eax+89A4h]
    L_0041fe56:
        mov dword ptr [esp+0Ch],43F00000h
    L_0041fe5e:
        mov dword ptr [esp+10h],43C40000h
    L_0041fe66:
        mov dword ptr [esp+14h],0
    L_0041fe6e:
        jne short L_0041fe8b
    L_0041fe70:
        mov eax,dword ptr [eax+8994h]
    L_0041fe76:
        push 6
    L_0041fe78:
        lea ecx,[esp+20h]
    L_0041fe7c:
        push ecx
    L_0041fe7d:
        push eax
    L_0041fe7e:
        lea edi,[esp+18h]
    L_0041fe82:
        call asm_AnimationManager_CreatePositionedPrimary_00448d50
    L_0041fe87:
        mov edx,dword ptr [eax]
    L_0041fe89:
        mov dword ptr [esi],edx
    L_0041fe8b:
        inc dword ptr [ebp+3E8h]
    L_0041fe91:
        mov eax,dword ptr [ebp+3ECh]
    L_0041fe97:
        pop edi
    L_0041fe98:
        inc eax
    L_0041fe99:
        mov dword ptr [ebp+3ECh],eax
    L_0041fe9f:
        pop esi
    L_0041fea0:
        mov eax,1
    L_0041fea5:
        pop ebp
    L_0041fea6:
        add esp,0Ch
    L_0041fea9:
        ret 4
    }
}
