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

// 0x00443F80..0x00443FA0: FUN_00443f80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443f80_00443f80() {
    __asm {
    L_00443f80:
        mov eax,esi
    L_00443f82:
        call asm_FUN_00443b60_00443b60
    L_00443f87:
        test eax,eax
    L_00443f89:
        je short L_00443f91
    L_00443f8b:
        or eax,0FFFFFFFFh
    L_00443f8e:
        ret 4
    L_00443f91:
        mov ecx,dword ptr [esp+4]
    L_00443f95:
        push 0
    L_00443f97:
        mov eax,esi
    L_00443f99:
        call asm_FUN_00442670_00442670
    L_00443f9e:
        ret 4
    }
}

// 0x00444580..0x004445BB: FUN_00444580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444580_00444580() {
    __asm {
    L_00444580:
        push edi
    L_00444581:
        mov eax,esi
    L_00444583:
        call asm_FUN_00444240_00444240
    L_00444588:
        push 0
    L_0044458a:
        mov eax,esi
    L_0044458c:
        mov ecx,edi
    L_0044458e:
        call asm_FUN_00442670_00442670
    L_00444593:
        mov dword ptr [data_00497920],3F800000h
    L_0044459d:
        mov dword ptr [data_00497904],3F800000h
    L_004445a7:
        mov dword ptr [data_004978e8],3F800000h
    L_004445b1:
        mov dword ptr [data_004978cc],3F800000h
    L_004445bb:
        ret
    }
}
