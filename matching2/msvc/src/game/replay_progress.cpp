#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FF0..0x0041304C: FUN_00412ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412ff0_00412ff0() {
    __asm {
    L_00412ff0:
        cmp dword ptr [edi+18h],82h
    L_00412ff7:
        jge short L_0041304a
    L_00412ff9:
        fild dword ptr [esp+4]
    L_00412ffd:
        push esi
    L_00412ffe:
        push ecx
    L_00412fff:
        lea esi,[edi+14h]
    L_00413002:
        fstp dword ptr [esp]
    L_00413005:
        call asm_FrameTimer_Advance_0044bf40
    L_0041300a:
        cmp dword ptr [edi+18h],82h
    L_00413011:
        jle short L_00413049
    L_00413013:
        mov eax,dword ptr [esi+10h]
    L_00413016:
        test al,1
    L_00413018:
        jne short L_00413035
    L_0041301a:
        xor ecx,ecx
    L_0041301c:
        or eax,1
    L_0041301f:
        mov dword ptr [esi+4],ecx
    L_00413022:
        mov dword ptr [esi],0FFF0BDC1h
    L_00413028:
        mov dword ptr [esi+8],ecx
    L_0041302b:
        mov dword ptr [esi+0Ch],476F78h
    L_00413032:
        mov dword ptr [esi+10h],eax
    L_00413035:
        mov dword ptr [esi+4],82h
    L_0041303c:
        mov dword ptr [esi+8],43020000h
    L_00413043:
        mov dword ptr [esi],81h
    L_00413049:
        pop esi
    L_0041304a:
        ret 4
    }
}

// 0x00415DB0..0x00415E2B: FUN_00415db0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415db0_00415db0() {
    __asm {
    L_00415db0:
        push 0FFFFFFFFh
    L_00415db2:
        push 46582Bh
    L_00415db7:
        mov eax,dword ptr fs:[0]
    L_00415dbd:
        push eax
    L_00415dbe:
        mov dword ptr fs:[0],esp
    L_00415dc5:
        push ecx
    L_00415dc6:
        push 90h
    L_00415dcb:
        call asm_operator_new_00452493
    L_00415dd0:
        add esp,4
    L_00415dd3:
        mov dword ptr [esp],eax
    L_00415dd6:
        test eax,eax
    L_00415dd8:
        mov dword ptr [esp+0Ch],0
    L_00415de0:
        je short L_00415df7
    L_00415de2:
        mov ecx,dword ptr [edi+9EBCh]
    L_00415de8:
        mov edx,dword ptr [ecx+esi*8+4]
    L_00415dec:
        add edx,ecx
    L_00415dee:
        push edx
    L_00415def:
        push eax
    L_00415df0:
        call asm_FUN_00415b00_00415b00
    L_00415df5:
        jmp short L_00415df9
    L_00415df7:
        xor eax,eax
    L_00415df9:
        mov dword ptr [edi+9EB8h],eax
    L_00415dff:
        mov dword ptr [eax],esi
    L_00415e01:
        mov ecx,dword ptr [data_00474c84]
    L_00415e07:
        lea eax,[esi+1]
    L_00415e0a:
        cmp ecx,eax
    L_00415e0c:
        mov dword ptr [data_00474c84],eax
    L_00415e11:
        je short L_00415e1d
    L_00415e13:
        mov dword ptr [data_00474c8c],0
    L_00415e1d:
        mov ecx,dword ptr [esp+4]
    L_00415e21:
        mov dword ptr fs:[0],ecx
    L_00415e28:
        add esp,10h
    L_00415e2b:
        ret
    }
}
