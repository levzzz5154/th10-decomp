#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452B40..0x00452B70: FUN_00452b40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452b40_00452b40() {
    __asm {
    L_00452b40:
        push ebp
    L_00452b41:
        mov ebp,esp
    L_00452b43:
        sub esp,20h
    L_00452b46:
        and dword ptr [ebp-18h],0
    L_00452b4a:
        and dword ptr [ebp-20h],0
    L_00452b4e:
        lea eax,[ebp+0Ch]
    L_00452b51:
        push eax
    L_00452b52:
        push dword ptr [ebp+8]
    L_00452b55:
        lea eax,[ebp-20h]
    L_00452b58:
        push eax
    L_00452b59:
        mov dword ptr [ebp-1Ch],7FFFFFFFh
    L_00452b60:
        mov dword ptr [ebp-14h],42h
    L_00452b67:
        call asm_FUN_00454ed7_00454ed7
    L_00452b6c:
        add esp,0Ch
    L_00452b6f:
        leave
    L_00452b70:
        ret
    }
}
