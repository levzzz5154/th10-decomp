#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E8B4..0x0045E8E0: __errcode
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_errcode_0045e8b4() {
    __asm {
    L_0045e8b4:
        mov al,byte ptr [esp+4]
    L_0045e8b8:
        test al,20h
    L_0045e8ba:
        je short L_0045e8c0
    L_0045e8bc:
        push 5
    L_0045e8be:
        jmp short L_0045e8d6
    L_0045e8c0:
        test al,8
    L_0045e8c2:
        je short L_0045e8c8
    L_0045e8c4:
        xor eax,eax
    L_0045e8c6:
        inc eax
    L_0045e8c7:
        ret
    L_0045e8c8:
        test al,4
    L_0045e8ca:
        je short L_0045e8d0
    L_0045e8cc:
        push 2
    L_0045e8ce:
        jmp short L_0045e8d6
    L_0045e8d0:
        test al,1
    L_0045e8d2:
        je short L_0045e8d8
    L_0045e8d4:
        push 3
    L_0045e8d6:
        pop eax
    L_0045e8d7:
        ret
    L_0045e8d8:
        movzx eax,al
    L_0045e8db:
        and eax,2
    L_0045e8de:
        shl eax,1
    L_0045e8e0:
        ret
    }
}
