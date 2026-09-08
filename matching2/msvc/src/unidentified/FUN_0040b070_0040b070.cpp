#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B070..0x0040B10E: FUN_0040b070
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b070_0040b070() {
    __asm {
    L_0040b070:
        push ebx
    L_0040b071:
        push ebp
    L_0040b072:
        shl eax,4
    L_0040b075:
        push esi
    L_0040b076:
        mov esi,dword ptr [data_00491c10]
    L_0040b07c:
        add eax,474430h
    L_0040b081:
        push edi
    L_0040b082:
        mov edi,eax
    L_0040b084:
        mov eax,dword ptr [esp+14h]
    L_0040b088:
        mov ecx,dword ptr [eax+10h]
    L_0040b08b:
        movsx ebp,word ptr [edi]
    L_0040b08e:
        mov dword ptr [esp+14h],ecx
    L_0040b092:
        call asm_FUN_00449950_00449950
    L_0040b097:
        mov ecx,dword ptr [esp+14h]
    L_0040b09b:
        mov ebx,eax
    L_0040b09d:
        mov eax,dword ptr [ebx+35Ch]
    L_0040b0a3:
        push ebp
    L_0040b0a4:
        or eax,40000000h
    L_0040b0a9:
        push ebx
    L_0040b0aa:
        mov dword ptr [ebx+20h],0Fh
    L_0040b0b1:
        mov dword ptr [ebx+35Ch],eax
    L_0040b0b7:
        call asm_FUN_00449870_00449870
    L_0040b0bc:
        mov esi,dword ptr [data_00491c10]
    L_0040b0c2:
        lea eax,[esp+14h]
    L_0040b0c6:
        mov edx,esi
    L_0040b0c8:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040b0cd:
        mov ebx,dword ptr [esp+14h]
    L_0040b0d1:
        push ebx
    L_0040b0d2:
        mov edx,esi
    L_0040b0d4:
        call asm_AnimationManager_Find_004491c0
    L_0040b0d9:
        mov esi,eax
    L_0040b0db:
        test esi,esi
    L_0040b0dd:
        jne short L_0040b0e1
    L_0040b0df:
        xor ebx,ebx
    L_0040b0e1:
        mov eax,dword ptr [edi+4]
    L_0040b0e4:
        test eax,eax
    L_0040b0e6:
        je short L_0040b0f0
    L_0040b0e8:
        mov edx,dword ptr [esp+1Ch]
    L_0040b0ec:
        mov ecx,esi
    L_0040b0ee:
        call eax
    L_0040b0f0:
        mov edx,dword ptr [edi+8]
    L_0040b0f3:
        mov dword ptr [esi+398h],edx
    L_0040b0f9:
        mov eax,dword ptr [edi+0Ch]
    L_0040b0fc:
        pop edi
    L_0040b0fd:
        mov dword ptr [esi+39Ch],eax
    L_0040b103:
        mov eax,dword ptr [esp+14h]
    L_0040b107:
        pop esi
    L_0040b108:
        pop ebp
    L_0040b109:
        mov dword ptr [eax],ebx
    L_0040b10b:
        pop ebx
    L_0040b10c:
        ret 0Ch
    }
}
