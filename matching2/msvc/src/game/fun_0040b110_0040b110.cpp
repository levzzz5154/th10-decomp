#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.

// 0x0040B110..0x0040B1A3: FUN_0040b110
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b110_0040b110() {
    __asm {
    L_0040b110:
        push ebx
    L_0040b111:
        push ebp
    L_0040b112:
        push esi
    L_0040b113:
        mov esi,dword ptr [data_00491c10]
    L_0040b119:
        shl eax,4
    L_0040b11c:
        add eax,474430h
    L_0040b121:
        push edi
    L_0040b122:
        mov edi,eax
    L_0040b124:
        movsx ebp,word ptr [edi]
    L_0040b127:
        call asm_FUN_00449950_00449950
    L_0040b12c:
        mov ecx,dword ptr [esp+18h]
    L_0040b130:
        mov ebx,eax
    L_0040b132:
        mov eax,dword ptr [ebx+35Ch]
    L_0040b138:
        push ebp
    L_0040b139:
        or eax,40000000h
    L_0040b13e:
        push ebx
    L_0040b13f:
        mov dword ptr [ebx+20h],0Fh
    L_0040b146:
        mov dword ptr [ebx+35Ch],eax
    L_0040b14c:
        call asm_FUN_00449870_00449870
    L_0040b151:
        mov esi,dword ptr [data_00491c10]
    L_0040b157:
        lea eax,[esp+18h]
    L_0040b15b:
        mov edx,esi
    L_0040b15d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040b162:
        mov ebx,dword ptr [esp+18h]
    L_0040b166:
        push ebx
    L_0040b167:
        mov edx,esi
    L_0040b169:
        call asm_AnimationManager_Find_004491c0
    L_0040b16e:
        mov esi,eax
    L_0040b170:
        test esi,esi
    L_0040b172:
        jne short L_0040b176
    L_0040b174:
        xor ebx,ebx
    L_0040b176:
        mov eax,dword ptr [edi+4]
    L_0040b179:
        test eax,eax
    L_0040b17b:
        je short L_0040b185
    L_0040b17d:
        mov edx,dword ptr [esp+1Ch]
    L_0040b181:
        mov ecx,esi
    L_0040b183:
        call eax
    L_0040b185:
        mov eax,dword ptr [edi+8]
    L_0040b188:
        mov dword ptr [esi+398h],eax
    L_0040b18e:
        mov ecx,dword ptr [edi+0Ch]
    L_0040b191:
        mov eax,dword ptr [esp+14h]
    L_0040b195:
        pop edi
    L_0040b196:
        mov dword ptr [esi+39Ch],ecx
    L_0040b19c:
        pop esi
    L_0040b19d:
        pop ebp
    L_0040b19e:
        mov dword ptr [eax],ebx
    L_0040b1a0:
        pop ebx
    L_0040b1a1:
        ret 0Ch
    }
}
