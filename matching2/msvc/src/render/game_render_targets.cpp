#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438A60..0x00438ACE: FUN_00438a60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00438a60_00438a60() {
    __asm {
    L_00438a60:
        push ebx
    L_00438a61:
        mov ebx,dword ptr [esi+4]
    L_00438a64:
        test ebx,ebx
    L_00438a66:
        jl short L_00438a99
    L_00438a68:
        mov eax,dword ptr [esi+24h]
    L_00438a6b:
        mov ecx,dword ptr [esi+20h]
    L_00438a6e:
        mov edx,dword ptr [esi+1Ch]
    L_00438a71:
        push eax
    L_00438a72:
        mov eax,dword ptr [esi+18h]
    L_00438a75:
        push ecx
    L_00438a76:
        mov ecx,dword ptr [esi+14h]
    L_00438a79:
        push edx
    L_00438a7a:
        mov edx,dword ptr [esi+10h]
    L_00438a7d:
        push eax
    L_00438a7e:
        mov eax,dword ptr [esi+0Ch]
    L_00438a81:
        push ecx
    L_00438a82:
        mov ecx,dword ptr [esi+8]
    L_00438a85:
        push edx
    L_00438a86:
        push eax
    L_00438a87:
        mov eax,dword ptr [esi+28h]
    L_00438a8a:
        push ecx
    L_00438a8b:
        mov ecx,esi
    L_00438a8d:
        call asm_FUN_00448270_00448270
    L_00438a92:
        mov dword ptr [esi+4],0FFFFFFFFh
    L_00438a99:
        mov eax,dword ptr [esi]
    L_00438a9b:
        test eax,eax
    L_00438a9d:
        pop ebx
    L_00438a9e:
        jl short L_00438ace
    L_00438aa0:
        mov edx,dword ptr [esi+48h]
    L_00438aa3:
        mov ecx,dword ptr [esi+44h]
    L_00438aa6:
        push edx
    L_00438aa7:
        mov edx,dword ptr [esi+40h]
    L_00438aaa:
        push ecx
    L_00438aab:
        mov ecx,dword ptr [esi+3Ch]
    L_00438aae:
        push edx
    L_00438aaf:
        mov edx,dword ptr [esi+38h]
    L_00438ab2:
        push ecx
    L_00438ab3:
        mov ecx,dword ptr [esi+34h]
    L_00438ab6:
        push edx
    L_00438ab7:
        mov edx,dword ptr [esi+30h]
    L_00438aba:
        push ecx
    L_00438abb:
        mov ecx,dword ptr [esi+2Ch]
    L_00438abe:
        push edx
    L_00438abf:
        push ecx
    L_00438ac0:
        push eax
    L_00438ac1:
        mov eax,esi
    L_00438ac3:
        call asm_FUN_00448450_00448450
    L_00438ac8:
        mov dword ptr [esi],0FFFFFFFFh
    L_00438ace:
        ret
    }
}


