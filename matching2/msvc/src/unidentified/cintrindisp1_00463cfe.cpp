#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463CFE..0x00463D3A: __cintrindisp1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cintrindisp1_00463cfe() {
    __asm {
    L_00463cfe:
        push ebp
    L_00463cff:
        mov ebp,esp
    L_00463d01:
        add esp,0FFFFFD30h
    L_00463d07:
        push ebx
    L_00463d08:
        wait
        fnstcw word ptr [ebp-0A4h]
    L_00463d0f:
        cmp dword ptr [data_00473c90],0
    L_00463d16:
        je short L_00463d33
    L_00463d18:
        call asm_trandisp1_00463f40
    L_00463d1d:
        or byte ptr [ebp-2C8h],1
    L_00463d24:
        and byte ptr [ebp-2C8h],0FDh
    L_00463d2b:
        call asm_FUN_00463d8a_00463d8a
    L_00463d30:
        pop ebx
    L_00463d31:
        leave
    L_00463d32:
        ret
    L_00463d33:
        fst qword ptr [ebp-86h]
    L_00463d39:
        jmp short L_00463d18
    }
}
