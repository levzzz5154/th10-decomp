#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413A20..0x00413B40: FUN_00413a20
// Naked body preserves the retail register/stack ABI.

// 0x0042AF20..0x0042AF80: FUN_0042af20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042af20_0042af20() {
    __asm {
    L_0042af20:
        push 0FFFFFFFFh
    L_0042af22:
        push 4655ABh
    L_0042af27:
        mov eax,dword ptr fs:[0]
    L_0042af2d:
        push eax
    L_0042af2e:
        mov dword ptr fs:[0],esp
    L_0042af35:
        push ecx
    L_0042af36:
        push 1DCB4h
    L_0042af3b:
        call asm_operator_new_00452493
    L_0042af40:
        add esp,4
    L_0042af43:
        mov dword ptr [esp],eax
    L_0042af46:
        test eax,eax
    L_0042af48:
        mov dword ptr [esp+0Ch],0
    L_0042af50:
        je short L_0042af6b
    L_0042af52:
        call asm_EffectManager_InitializePoolsRetail_0042ae60
    L_0042af57:
        mov dword ptr [data_0047783c],eax
    L_0042af5c:
        mov ecx,dword ptr [esp+4]
    L_0042af60:
        mov dword ptr fs:[0],ecx
    L_0042af67:
        add esp,10h
    L_0042af6a:
        ret
    L_0042af6b:
        mov ecx,dword ptr [esp+4]
    L_0042af6f:
        xor eax,eax
    L_0042af71:
        mov dword ptr [data_0047783c],eax
    L_0042af76:
        mov dword ptr fs:[0],ecx
    L_0042af7d:
        add esp,10h
    L_0042af80:
        ret
    }
}
