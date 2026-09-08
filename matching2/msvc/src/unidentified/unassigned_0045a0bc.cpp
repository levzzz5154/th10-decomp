#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A0BC..0x0045A0EA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045a0bc() {
    __asm {
    L_0045a0bc:
        mov eax,dword ptr [esp+4]
    L_0045a0c0:
        mov ecx,473740h
    L_0045a0c5:
        cmp eax,ecx
    L_0045a0c7:
        jb short L_0045a0e0
    L_0045a0c9:
        cmp eax,4739A0h
    L_0045a0ce:
        ja short L_0045a0e0
    L_0045a0d0:
        sub eax,ecx
    L_0045a0d2:
        sar eax,5
    L_0045a0d5:
        add eax,10h
    L_0045a0d8:
        push eax
    L_0045a0d9:
        call asm_FUN_00453b3f_00453b3f
    L_0045a0de:
        pop ecx
    L_0045a0df:
        ret
    L_0045a0e0:
        add eax,20h
    L_0045a0e3:
        push eax
    L_0045a0e4:
        call dword ptr [data_004660b4]
    L_0045a0ea:
        ret
    }
}
