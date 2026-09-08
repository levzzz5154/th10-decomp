#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B1B0..0x0040B242: FUN_0040b1b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b1b0_0040b1b0() {
    __asm {
    L_0040b1b0:
        push ebx
    L_0040b1b1:
        push ebp
    L_0040b1b2:
        mov ebp,dword ptr [esp+0Ch]
    L_0040b1b6:
        push esi
    L_0040b1b7:
        mov esi,dword ptr [data_00491c10]
    L_0040b1bd:
        push edi
    L_0040b1be:
        call asm_FUN_00449950_00449950
    L_0040b1c3:
        mov ecx,dword ptr [esp+18h]
    L_0040b1c7:
        mov ebx,eax
    L_0040b1c9:
        movsx eax,word ptr [esp+1Ch]
    L_0040b1ce:
        mov edi,dword ptr [ebx+35Ch]
    L_0040b1d4:
        push eax
    L_0040b1d5:
        or edi,40000000h
    L_0040b1db:
        push ebx
    L_0040b1dc:
        mov dword ptr [ebx+20h],0Fh
    L_0040b1e3:
        mov dword ptr [ebx+35Ch],edi
    L_0040b1e9:
        call asm_FUN_00449870_00449870
    L_0040b1ee:
        mov esi,dword ptr [data_00491c10]
    L_0040b1f4:
        lea eax,[esp+1Ch]
    L_0040b1f8:
        mov edx,esi
    L_0040b1fa:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040b1ff:
        mov edi,dword ptr [esp+1Ch]
    L_0040b203:
        push edi
    L_0040b204:
        mov edx,esi
    L_0040b206:
        call asm_AnimationManager_Find_004491c0
    L_0040b20b:
        mov esi,eax
    L_0040b20d:
        test esi,esi
    L_0040b20f:
        jne short L_0040b213
    L_0040b211:
        xor edi,edi
    L_0040b213:
        mov eax,dword ptr [esp+24h]
    L_0040b217:
        test eax,eax
    L_0040b219:
        je short L_0040b223
    L_0040b21b:
        mov edx,dword ptr [esp+20h]
    L_0040b21f:
        mov ecx,esi
    L_0040b221:
        call eax
    L_0040b223:
        mov ecx,dword ptr [esp+28h]
    L_0040b227:
        mov edx,dword ptr [esp+2Ch]
    L_0040b22b:
        mov dword ptr [esi+398h],ecx
    L_0040b231:
        mov dword ptr [esi+39Ch],edx
    L_0040b237:
        mov dword ptr [ebp],edi
    L_0040b23a:
        pop edi
    L_0040b23b:
        pop esi
    L_0040b23c:
        mov eax,ebp
    L_0040b23e:
        pop ebp
    L_0040b23f:
        pop ebx
    L_0040b240:
        ret 1Ch
    }
}
