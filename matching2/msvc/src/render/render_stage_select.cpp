#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401D20..0x00401D5B: GameThread_SelectRenderStageRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_SelectRenderStageRetail_00401d20() {
    __asm {
    L_00401d20:
        mov eax,ebx
    L_00401d22:
        imul eax,118h
    L_00401d28:
        push edi
    L_00401d29:
        lea edi,[eax+esi+154h]
    L_00401d30:
        mov dword ptr [esi+384h],edi
    L_00401d36:
        call asm_FUN_004215a0_004215a0
    L_00401d3b:
        mov edx,dword ptr [esi+384h]
    L_00401d41:
        mov eax,dword ptr [esi+8]
    L_00401d44:
        mov ecx,dword ptr [eax]
    L_00401d46:
        add edx,0CCh
    L_00401d4c:
        push edx
    L_00401d4d:
        push eax
    L_00401d4e:
        call dword ptr [ecx+0BCh]
    L_00401d54:
        mov dword ptr [esi+388h],ebx
    L_00401d5a:
        pop edi
    L_00401d5b:
        ret
    }
}
