#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004524FD..0x0045252C: FUN_004524fd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004524fd_004524fd() {
    __asm {
    L_004524fd:
        push ebp
    L_004524fe:
        mov ebp,esp
    L_00452500:
        sub esp,20h
    L_00452503:
        push dword ptr [ebp+0Ch]
    L_00452506:
        and dword ptr [ebp-18h],0
    L_0045250a:
        push dword ptr [ebp+8]
    L_0045250d:
        and dword ptr [ebp-20h],0
    L_00452511:
        lea eax,[ebp-20h]
    L_00452514:
        push eax
    L_00452515:
        mov dword ptr [ebp-1Ch],7FFFFFFFh
    L_0045251c:
        mov dword ptr [ebp-14h],42h
    L_00452523:
        call asm_FUN_00454ed7_00454ed7
    L_00452528:
        add esp,0Ch
    L_0045252b:
        leave
    L_0045252c:
        ret
    }
}
