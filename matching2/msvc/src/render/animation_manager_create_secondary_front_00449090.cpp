#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449090..0x004490D8: ?AnimationManager_CreateSecondaryFront@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_CreateSecondaryFront_00449090() {
    __asm {
    L_00449090:
        push ebx
    L_00449091:
        push esi
    L_00449092:
        mov esi,dword ptr [data_00491c10]
    L_00449098:
        call asm_FUN_00449950_00449950
    L_0044909d:
        mov ecx,dword ptr [esp+10h]
    L_004490a1:
        mov ebx,eax
    L_004490a3:
        mov esi,dword ptr [ebx+35Ch]
    L_004490a9:
        mov eax,dword ptr [esp+14h]
    L_004490ad:
        push ecx
    L_004490ae:
        mov ecx,dword ptr [esp+10h]
    L_004490b2:
        or esi,40000000h
    L_004490b8:
        push ebx
    L_004490b9:
        mov dword ptr [ebx+20h],eax
    L_004490bc:
        mov dword ptr [ebx+35Ch],esi
    L_004490c2:
        call asm_FUN_00449870_00449870
    L_004490c7:
        mov edx,dword ptr [data_00491c10]
    L_004490cd:
        mov eax,edi
    L_004490cf:
        call asm_AnimationManager_RegisterSecondaryFront_00448b40
    L_004490d4:
        pop esi
    L_004490d5:
        pop ebx
    L_004490d6:
        ret 0Ch
    }
}
