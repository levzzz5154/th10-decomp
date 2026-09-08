#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401FD0..0x00401FEE: FUN_00401fd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401fd0_00401fd0() {
    __asm {
    L_00401fd0:
        dec eax
    L_00401fd1:
        push ebp
    L_00401fd2:
        mov ebp,dword ptr [esp+8]
    L_00401fd6:
        push esi
    L_00401fd7:
        mov esi,ecx
    L_00401fd9:
        js short L_00401fea
    L_00401fdb:
        push edi
    L_00401fdc:
        lea edi,[eax+1]
    L_00401fdf:
        nop
    L_00401fe0:
        mov ecx,esi
    L_00401fe2:
        call ebx
    L_00401fe4:
        add esi,ebp
    L_00401fe6:
        dec edi
    L_00401fe7:
        jne short L_00401fe0
    L_00401fe9:
        pop edi
    L_00401fea:
        pop esi
    L_00401feb:
        pop ebp
    L_00401fec:
        ret 4
    }
}
