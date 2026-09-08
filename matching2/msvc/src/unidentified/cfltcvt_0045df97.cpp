#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DF97..0x0045DFE7: __cfltcvt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cfltcvt_0045df97() {
    __asm {
    L_0045df97:
        push ebp
    L_0045df98:
        mov ebp,esp
    L_0045df9a:
        cmp dword ptr [ebp+10h],65h
    L_0045df9e:
        je short L_0045dfd2
    L_0045dfa0:
        cmp dword ptr [ebp+10h],45h
    L_0045dfa4:
        je short L_0045dfd2
    L_0045dfa6:
        cmp dword ptr [ebp+10h],66h
    L_0045dfaa:
        jne short L_0045dfbf
    L_0045dfac:
        push dword ptr [ebp+14h]
    L_0045dfaf:
        push dword ptr [ebp+0Ch]
    L_0045dfb2:
        push dword ptr [ebp+8]
    L_0045dfb5:
        call asm_FUN_0045de91_0045de91
    L_0045dfba:
        add esp,0Ch
    L_0045dfbd:
        pop ebp
    L_0045dfbe:
        ret
    L_0045dfbf:
        push dword ptr [ebp+18h]
    L_0045dfc2:
        push dword ptr [ebp+14h]
    L_0045dfc5:
        push dword ptr [ebp+0Ch]
    L_0045dfc8:
        push dword ptr [ebp+8]
    L_0045dfcb:
        call asm_FUN_0045def8_0045def8
    L_0045dfd0:
        jmp short L_0045dfe3
    L_0045dfd2:
        push dword ptr [ebp+18h]
    L_0045dfd5:
        push dword ptr [ebp+14h]
    L_0045dfd8:
        push dword ptr [ebp+0Ch]
    L_0045dfdb:
        push dword ptr [ebp+8]
    L_0045dfde:
        call asm_FUN_0045dd85_0045dd85
    L_0045dfe3:
        add esp,10h
    L_0045dfe6:
        pop ebp
    L_0045dfe7:
        ret
    }
}
