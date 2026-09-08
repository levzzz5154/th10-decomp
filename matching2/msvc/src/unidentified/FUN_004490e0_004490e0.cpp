#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004490E0..0x0044913E: FUN_004490e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004490e0_004490e0() {
    __asm {
    L_004490e0:
        push ebx
    L_004490e1:
        push ebp
    L_004490e2:
        mov ebp,dword ptr [esp+10h]
    L_004490e6:
        push esi
    L_004490e7:
        mov esi,dword ptr [data_00491c10]
    L_004490ed:
        call asm_FUN_00449950_00449950
    L_004490f2:
        mov ebx,dword ptr [esp+18h]
    L_004490f6:
        mov esi,eax
    L_004490f8:
        or dword ptr [esi+35Ch],40000000h
    L_00449102:
        mov dword ptr [esi+20h],0
    L_00449109:
        mov ecx,dword ptr [edi]
    L_0044910b:
        lea eax,[esi+340h]
    L_00449111:
        mov dword ptr [eax],ecx
    L_00449113:
        mov edx,dword ptr [edi+4]
    L_00449116:
        mov dword ptr [eax+4],edx
    L_00449119:
        mov ecx,dword ptr [edi+8]
    L_0044911c:
        mov dword ptr [eax+8],ecx
    L_0044911f:
        mov ecx,dword ptr [esp+10h]
    L_00449123:
        mov eax,esi
    L_00449125:
        call asm_AnimationObject_LoadScript_0043e710
    L_0044912a:
        mov edx,dword ptr [data_00491c10]
    L_00449130:
        mov ebx,esi
    L_00449132:
        mov eax,ebp
    L_00449134:
        call asm_AnimationManager_RegisterSecondaryFront_00448b40
    L_00449139:
        pop esi
    L_0044913a:
        pop ebp
    L_0044913b:
        pop ebx
    L_0044913c:
        ret 0Ch
    }
}
