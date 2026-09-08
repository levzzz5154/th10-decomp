#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A0EB..0x0045A10D: __unlock_file2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unlock_file2_0045a0eb() {
    __asm {
    L_0045a0eb:
        mov eax,dword ptr [esp+4]
    L_0045a0ef:
        cmp eax,14h
    L_0045a0f2:
        jge short L_0045a0ff
    L_0045a0f4:
        add eax,10h
    L_0045a0f7:
        push eax
    L_0045a0f8:
        call asm_FUN_00453b3f_00453b3f
    L_0045a0fd:
        pop ecx
    L_0045a0fe:
        ret
    L_0045a0ff:
        mov eax,dword ptr [esp+8]
    L_0045a103:
        add eax,20h
    L_0045a106:
        push eax
    L_0045a107:
        call dword ptr [data_004660b4]
    L_0045a10d:
        ret
    }
}
