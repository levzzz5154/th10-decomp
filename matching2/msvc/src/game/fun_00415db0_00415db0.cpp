#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FF0..0x0041304C: FUN_00412ff0
// Naked body preserves the retail register/stack ABI.

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
