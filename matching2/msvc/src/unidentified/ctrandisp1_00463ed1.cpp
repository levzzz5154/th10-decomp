#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463ED1..0x00463F03: __ctrandisp1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ctrandisp1_00463ed1() {
    __asm {
    L_00463ed1:
        push ebp
    L_00463ed2:
        mov ebp,esp
    L_00463ed4:
        add esp,0FFFFFD30h
    L_00463eda:
        push ebx
    L_00463edb:
        push dword ptr [ebp+0Ch]
    L_00463ede:
        push dword ptr [ebp+8]
    L_00463ee1:
        call asm_fload_00463f04
    L_00463ee6:
        add esp,8
    L_00463ee9:
        wait
        fnstcw word ptr [ebp-0A4h]
    L_00463ef0:
        and byte ptr [ebp-2C8h],0FDh
    L_00463ef7:
        call asm_trandisp1_00463f40
    L_00463efc:
        call asm_FUN_00463d83_00463d83
    L_00463f01:
        pop ebx
    L_00463f02:
        leave
    L_00463f03:
        ret
    }
}
