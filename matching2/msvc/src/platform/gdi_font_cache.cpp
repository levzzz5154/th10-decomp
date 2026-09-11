#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436A30..0x00436A9A: FontCache_FlushRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FontCache_FlushRetail_00436a30() {
    __asm {
    L_00436a30:
        mov eax,dword ptr [esi+114h]
    L_00436a36:
        push edi
    L_00436a37:
        xor edi,edi
    L_00436a39:
        cmp eax,edi
    L_00436a3b:
        je short L_00436a97
    L_00436a3d:
        mov ecx,dword ptr [esi+118h]
    L_00436a43:
        push ecx
    L_00436a44:
        push eax
    L_00436a45:
        call dword ptr [data_0046602c]
    L_00436a4b:
        mov edx,dword ptr [esi+114h]
    L_00436a51:
        push edx
    L_00436a52:
        call dword ptr [data_00466028]
    L_00436a58:
        mov eax,dword ptr [esi+11Ch]
    L_00436a5e:
        push eax
    L_00436a5f:
        call dword ptr [data_00466030]
    L_00436a65:
        mov dword ptr [esi+104h],edi
    L_00436a6b:
        mov dword ptr [esi+108h],edi
    L_00436a71:
        mov dword ptr [esi+114h],edi
    L_00436a77:
        mov dword ptr [esi+11Ch],edi
    L_00436a7d:
        mov dword ptr [esi+118h],edi
    L_00436a83:
        mov dword ptr [esi+120h],edi
    L_00436a89:
        mov dword ptr [esi+100h],0FFFFFFFFh
    L_00436a93:
        mov al,1
    L_00436a95:
        pop edi
    L_00436a96:
        ret
    L_00436a97:
        xor al,al
    L_00436a99:
        pop edi
    L_00436a9a:
        ret
    }
}

