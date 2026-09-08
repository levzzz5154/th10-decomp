#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448EE0..0x00448F55: FUN_00448ee0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448ee0_00448ee0() {
    __asm {
    L_00448ee0:
        push ebx
    L_00448ee1:
        push ebp
    L_00448ee2:
        mov ebp,dword ptr [esp+10h]
    L_00448ee6:
        push esi
    L_00448ee7:
        mov esi,dword ptr [data_00491c10]
    L_00448eed:
        call asm_FUN_00449950_00449950
    L_00448ef2:
        mov esi,eax
    L_00448ef4:
        mov eax,dword ptr [esi+35Ch]
    L_00448efa:
        mov ebx,dword ptr [esp+18h]
    L_00448efe:
        mov ecx,dword ptr [esp+10h]
    L_00448f02:
        mov dword ptr [esi+20h],0
    L_00448f09:
        or eax,40000000h
    L_00448f0e:
        mov dword ptr [esi+35Ch],eax
    L_00448f14:
        fld dword ptr [edi]
    L_00448f16:
        fadd dword ptr [data_00470b4c]
    L_00448f1c:
        fstp dword ptr [esi+340h]
    L_00448f22:
        fld dword ptr [edi+4]
    L_00448f25:
        fadd dword ptr [data_00470b48]
    L_00448f2b:
        fstp dword ptr [esi+344h]
    L_00448f31:
        mov eax,dword ptr [edi+8]
    L_00448f34:
        mov dword ptr [esi+348h],eax
    L_00448f3a:
        mov eax,esi
    L_00448f3c:
        call asm_AnimationObject_LoadScript_0043e710
    L_00448f41:
        mov edx,dword ptr [data_00491c10]
    L_00448f47:
        mov ebx,esi
    L_00448f49:
        mov eax,ebp
    L_00448f4b:
        call asm_AnimationManager_RegisterPrimaryFront_00448a50
    L_00448f50:
        pop esi
    L_00448f51:
        pop ebp
    L_00448f52:
        pop ebx
    L_00448f53:
        ret 0Ch
    }
}
