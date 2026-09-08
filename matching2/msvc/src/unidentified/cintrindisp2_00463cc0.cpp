#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463CC0..0x00463CFD: __cintrindisp2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cintrindisp2_00463cc0() {
    __asm {
    L_00463cc0:
        push ebp
    L_00463cc1:
        mov ebp,esp
    L_00463cc3:
        add esp,0FFFFFD30h
    L_00463cc9:
        push ebx
    L_00463cca:
        wait
        fnstcw word ptr [ebp-0A4h]
    L_00463cd1:
        wait
    L_00463cd2:
        cmp dword ptr [data_00473c90],0
    L_00463cd9:
        je short L_00463cef
    L_00463cdb:
        call asm_trandisp2_00463fa7
    L_00463ce0:
        or byte ptr [ebp-2C8h],3
    L_00463ce7:
        call asm_FUN_00463d8a_00463d8a
    L_00463cec:
        pop ebx
    L_00463ced:
        leave
    L_00463cee:
        ret
    L_00463cef:
        fxch
    L_00463cf1:
        fst qword ptr [ebp-86h]
    L_00463cf7:
        fxch
    L_00463cf9:
        fst qword ptr [ebp-7Eh]
    L_00463cfc:
        jmp short L_00463cdb
    }
}
