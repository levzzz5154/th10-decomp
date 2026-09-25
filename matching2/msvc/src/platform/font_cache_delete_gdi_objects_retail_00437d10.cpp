#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=5/149; first_diff=extent (readable
// candidate emitted 196 bytes, retail extent 149); residual_class=private
// ESI receiver plus imported DeleteObject call scheduling; variants_tested=
// typed GDI import loop with live Ghidra DeleteObject/FUN_00436a30 topology
// and MSVC 13.10 probe; next_lever=native-LTCG cluster with
// FontCache_FlushRetail and its real caller to recover the ESI/EDI schedule.

// 0x00436A30..0x00436A9A: FontCache_FlushRetail
// Naked body preserves the retail register/stack ABI.

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
