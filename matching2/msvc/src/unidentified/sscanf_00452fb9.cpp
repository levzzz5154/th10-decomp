#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452FB9..0x00452FEC: _sscanf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_sscanf_00452fb9() {
    __asm {
    L_00452fb9:
        push ebp
    L_00452fba:
        mov ebp,esp
    L_00452fbc:
        sub esp,20h
    L_00452fbf:
        mov eax,dword ptr [ebp+8]
    L_00452fc2:
        push eax
    L_00452fc3:
        mov dword ptr [ebp-14h],49h
    L_00452fca:
        mov dword ptr [ebp-18h],eax
    L_00452fcd:
        mov dword ptr [ebp-20h],eax
    L_00452fd0:
        call asm_strlen_00456720
    L_00452fd5:
        mov dword ptr [ebp-1Ch],eax
    L_00452fd8:
        lea eax,[ebp+10h]
    L_00452fdb:
        push eax
    L_00452fdc:
        push dword ptr [ebp+0Ch]
    L_00452fdf:
        lea eax,[ebp-20h]
    L_00452fe2:
        push eax
    L_00452fe3:
        call asm_FUN_00457a7c_00457a7c
    L_00452fe8:
        add esp,10h
    L_00452feb:
        leave
    L_00452fec:
        ret
    }
}
