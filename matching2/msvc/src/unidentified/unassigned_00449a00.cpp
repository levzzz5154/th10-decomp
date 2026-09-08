#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A00..0x00449A19: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a00() {
    __asm {
    L_00449a00:
        lea edx,[ecx+68h]
    L_00449a03:
        cmp eax,edx
    L_00449a05:
        jb short L_00449a17
    L_00449a07:
        add ecx,3AC068h
    L_00449a0d:
        cmp eax,ecx
    L_00449a0f:
        jae short L_00449a17
    L_00449a11:
        mov eax,1
    L_00449a16:
        ret
    L_00449a17:
        xor eax,eax
    L_00449a19:
        ret
    }
}
