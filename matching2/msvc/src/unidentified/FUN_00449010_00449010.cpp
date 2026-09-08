#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449010..0x00449085: FUN_00449010
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449010_00449010() {
    __asm {
    L_00449010:
        push ebx
    L_00449011:
        push ebp
    L_00449012:
        mov ebp,dword ptr [esp+10h]
    L_00449016:
        push esi
    L_00449017:
        mov esi,dword ptr [data_00491c10]
    L_0044901d:
        call asm_FUN_00449950_00449950
    L_00449022:
        mov esi,eax
    L_00449024:
        mov eax,dword ptr [esi+35Ch]
    L_0044902a:
        mov ebx,dword ptr [esp+18h]
    L_0044902e:
        mov ecx,dword ptr [esp+10h]
    L_00449032:
        mov dword ptr [esi+20h],0
    L_00449039:
        or eax,40000000h
    L_0044903e:
        mov dword ptr [esi+35Ch],eax
    L_00449044:
        fld dword ptr [edi]
    L_00449046:
        fadd dword ptr [data_00470b4c]
    L_0044904c:
        fstp dword ptr [esi+340h]
    L_00449052:
        fld dword ptr [edi+4]
    L_00449055:
        fadd dword ptr [data_00470b48]
    L_0044905b:
        fstp dword ptr [esi+344h]
    L_00449061:
        mov eax,dword ptr [edi+8]
    L_00449064:
        mov dword ptr [esi+348h],eax
    L_0044906a:
        mov eax,esi
    L_0044906c:
        call asm_AnimationObject_LoadScript_0043e710
    L_00449071:
        mov edx,dword ptr [data_00491c10]
    L_00449077:
        mov ebx,esi
    L_00449079:
        mov eax,ebp
    L_0044907b:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00449080:
        pop esi
    L_00449081:
        pop ebp
    L_00449082:
        pop ebx
    L_00449083:
        ret 0Ch
    }
}
