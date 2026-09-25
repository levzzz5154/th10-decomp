#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004525A1..0x004525CF: __ArrayUnwind
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ArrayUnwind_004525a1() {
    __asm {
    L_004525a1:
        push 14h
    L_004525a3:
        push 46A6B0h
    L_004525a8:
        call asm_SEH_prolog_00454bbc
    L_004525ad:
        and dword ptr [ebp-4],0
    L_004525b1:
        dec dword ptr [ebp+10h]
    L_004525b4:
        js short L_004525c4
    L_004525b6:
        mov ecx,dword ptr [ebp+8]
    L_004525b9:
        sub ecx,dword ptr [ebp+0Ch]
    L_004525bc:
        mov dword ptr [ebp+8],ecx
    L_004525bf:
        call dword ptr [ebp+14h]
    L_004525c2:
        jmp short L_004525b1
    L_004525c4:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004525c8:
        call asm_SEH_epilog_00454bf7
    L_004525cd:
        ret 10h
    }
}
