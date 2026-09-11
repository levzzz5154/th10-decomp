#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00448DB0..0x00448E25: ?PlayerAnimation_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PlayerAnimation_Create_00448db0() {
    __asm {
    L_00448db0:
        push ebx
    L_00448db1:
        push ebp
    L_00448db2:
        mov ebp,dword ptr [esp+10h]
    L_00448db6:
        push esi
    L_00448db7:
        mov esi,dword ptr [data_00491c10]
    L_00448dbd:
        call asm_FUN_00449950_00449950
    L_00448dc2:
        mov esi,eax
    L_00448dc4:
        mov eax,dword ptr [esi+35Ch]
    L_00448dca:
        mov ebx,dword ptr [esp+18h]
    L_00448dce:
        mov ecx,dword ptr [esp+10h]
    L_00448dd2:
        mov dword ptr [esi+20h],0
    L_00448dd9:
        or eax,40000000h
    L_00448dde:
        mov dword ptr [esi+35Ch],eax
    L_00448de4:
        fld dword ptr [edi]
    L_00448de6:
        fadd dword ptr [data_00470b4c]
    L_00448dec:
        fstp dword ptr [esi+340h]
    L_00448df2:
        fld dword ptr [edi+4]
    L_00448df5:
        fadd dword ptr [data_00470b48]
    L_00448dfb:
        fstp dword ptr [esi+344h]
    L_00448e01:
        mov eax,dword ptr [edi+8]
    L_00448e04:
        mov dword ptr [esi+348h],eax
    L_00448e0a:
        mov eax,esi
    L_00448e0c:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448e11:
        mov edx,dword ptr [data_00491c10]
    L_00448e17:
        mov ebx,esi
    L_00448e19:
        mov eax,ebp
    L_00448e1b:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00448e20:
        pop esi
    L_00448e21:
        pop ebp
    L_00448e22:
        pop ebx
    L_00448e23:
        ret 0Ch
    }
}
