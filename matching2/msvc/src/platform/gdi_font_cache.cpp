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

// 0x00437D10..0x00437DA4: FontCache_DeleteGdiObjectsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FontCache_DeleteGdiObjectsRetail_00437d10() {
    __asm {
    L_00437d10:
        push esi
    L_00437d11:
        mov esi,474CB0h
    L_00437d16:
        call asm_FontCache_FlushRetail_00436a30
    L_00437d1b:
        mov eax,dword ptr [data_004918a0]
    L_00437d20:
        mov esi,dword ptr [data_00466030]
    L_00437d26:
        push eax
    L_00437d27:
        call esi
    L_00437d29:
        mov ecx,dword ptr [data_0049189c]
    L_00437d2f:
        push ecx
    L_00437d30:
        call esi
    L_00437d32:
        mov edx,dword ptr [data_00491898]
    L_00437d38:
        push edx
    L_00437d39:
        call esi
    L_00437d3b:
        mov eax,dword ptr [data_00491894]
    L_00437d40:
        push eax
    L_00437d41:
        call esi
    L_00437d43:
        mov ecx,dword ptr [data_00491890]
    L_00437d49:
        push ecx
    L_00437d4a:
        call esi
    L_00437d4c:
        mov edx,dword ptr [data_0049188c]
    L_00437d52:
        push edx
    L_00437d53:
        call esi
    L_00437d55:
        mov eax,dword ptr [data_00491888]
    L_00437d5a:
        push eax
    L_00437d5b:
        call esi
    L_00437d5d:
        mov ecx,dword ptr [data_00491884]
    L_00437d63:
        push ecx
    L_00437d64:
        call esi
    L_00437d66:
        mov edx,dword ptr [data_00491880]
    L_00437d6c:
        push edx
    L_00437d6d:
        call esi
    L_00437d6f:
        mov eax,dword ptr [data_0049187c]
    L_00437d74:
        push eax
    L_00437d75:
        call esi
    L_00437d77:
        mov ecx,dword ptr [data_00491878]
    L_00437d7d:
        push ecx
    L_00437d7e:
        call esi
    L_00437d80:
        mov edx,dword ptr [data_00491874]
    L_00437d86:
        push edx
    L_00437d87:
        call esi
    L_00437d89:
        mov eax,dword ptr [data_00491870]
    L_00437d8e:
        push eax
    L_00437d8f:
        call esi
    L_00437d91:
        mov ecx,dword ptr [data_0049186c]
    L_00437d97:
        push ecx
    L_00437d98:
        call esi
    L_00437d9a:
        mov edx,dword ptr [data_00491868]
    L_00437da0:
        push edx
    L_00437da1:
        call esi
    L_00437da3:
        pop esi
    L_00437da4:
        ret
    }
}
