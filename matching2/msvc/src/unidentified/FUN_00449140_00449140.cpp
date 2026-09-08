#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449140..0x004491B5: FUN_00449140
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449140_00449140() {
    __asm {
    L_00449140:
        push ebx
    L_00449141:
        push ebp
    L_00449142:
        mov ebp,dword ptr [esp+10h]
    L_00449146:
        push esi
    L_00449147:
        mov esi,dword ptr [data_00491c10]
    L_0044914d:
        call asm_FUN_00449950_00449950
    L_00449152:
        mov esi,eax
    L_00449154:
        mov eax,dword ptr [esi+35Ch]
    L_0044915a:
        mov ebx,dword ptr [esp+18h]
    L_0044915e:
        mov ecx,dword ptr [esp+10h]
    L_00449162:
        mov dword ptr [esi+20h],0
    L_00449169:
        or eax,40000000h
    L_0044916e:
        mov dword ptr [esi+35Ch],eax
    L_00449174:
        fld dword ptr [edi]
    L_00449176:
        fadd dword ptr [data_00470b4c]
    L_0044917c:
        fstp dword ptr [esi+340h]
    L_00449182:
        fld dword ptr [edi+4]
    L_00449185:
        fadd dword ptr [data_00470b48]
    L_0044918b:
        fstp dword ptr [esi+344h]
    L_00449191:
        mov eax,dword ptr [edi+8]
    L_00449194:
        mov dword ptr [esi+348h],eax
    L_0044919a:
        mov eax,esi
    L_0044919c:
        call asm_AnimationObject_LoadScript_0043e710
    L_004491a1:
        mov edx,dword ptr [data_00491c10]
    L_004491a7:
        mov ebx,esi
    L_004491a9:
        mov eax,ebp
    L_004491ab:
        call asm_AnimationManager_RegisterSecondaryFront_00448b40
    L_004491b0:
        pop esi
    L_004491b1:
        pop ebp
    L_004491b2:
        pop ebx
    L_004491b3:
        ret 0Ch
    }
}
