#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A099..0x0045A0BB: __lock_file2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lock_file2_0045a099() {
    __asm {
    L_0045a099:
        mov eax,dword ptr [esp+4]
    L_0045a09d:
        cmp eax,14h
    L_0045a0a0:
        jge short L_0045a0ad
    L_0045a0a2:
        add eax,10h
    L_0045a0a5:
        push eax
    L_0045a0a6:
        call asm_lock_00453c0c
    L_0045a0ab:
        pop ecx
    L_0045a0ac:
        ret
    L_0045a0ad:
        mov eax,dword ptr [esp+8]
    L_0045a0b1:
        add eax,20h
    L_0045a0b4:
        push eax
    L_0045a0b5:
        call dword ptr [data_004660b0]
    L_0045a0bb:
        ret
    }
}
