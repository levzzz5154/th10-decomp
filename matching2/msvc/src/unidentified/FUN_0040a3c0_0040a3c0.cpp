#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A3C0..0x0040A402: FUN_0040a3c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a3c0_0040a3c0() {
    __asm {
    L_0040a3c0:
        push ebx
    L_0040a3c1:
        push 688h
    L_0040a3c6:
        call asm_operator_new_00452493
    L_0040a3cb:
        add esp,4
    L_0040a3ce:
        test eax,eax
    L_0040a3d0:
        je short L_0040a3dd
    L_0040a3d2:
        mov edx,eax
    L_0040a3d4:
        call asm_FUN_0040a040_0040a040
    L_0040a3d9:
        mov ebx,eax
    L_0040a3db:
        jmp short L_0040a3df
    L_0040a3dd:
        xor ebx,ebx
    L_0040a3df:
        call asm_FUN_0040a130_0040a130
    L_0040a3e4:
        test eax,eax
    L_0040a3e6:
        je short L_0040a3ff
    L_0040a3e8:
        test ebx,ebx
    L_0040a3ea:
        je short L_0040a3fb
    L_0040a3ec:
        push ebx
    L_0040a3ed:
        call asm_FUN_0040a1a0_0040a1a0
    L_0040a3f2:
        push ebx
    L_0040a3f3:
        call asm_free_004524a1
    L_0040a3f8:
        add esp,4
    L_0040a3fb:
        xor eax,eax
    L_0040a3fd:
        pop ebx
    L_0040a3fe:
        ret
    L_0040a3ff:
        mov eax,ebx
    L_0040a401:
        pop ebx
    L_0040a402:
        ret
    }
}
