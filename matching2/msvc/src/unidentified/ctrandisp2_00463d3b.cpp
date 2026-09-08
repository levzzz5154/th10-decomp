#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463D3B..0x00463D82: __ctrandisp2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ctrandisp2_00463d3b() {
    __asm {
    L_00463d3b:
        push ebp
    L_00463d3c:
        mov ebp,esp
    L_00463d3e:
        add esp,0FFFFFD30h
    L_00463d44:
        push ebx
    L_00463d45:
        push dword ptr [ebp+0Ch]
    L_00463d48:
        push dword ptr [ebp+8]
    L_00463d4b:
        call asm_fload_00463f04
    L_00463d50:
        add esp,8
    L_00463d53:
        push dword ptr [ebp+14h]
    L_00463d56:
        push dword ptr [ebp+10h]
    L_00463d59:
        call asm_fload_00463f04
    L_00463d5e:
        add esp,8
    L_00463d61:
        wait
        fnstcw word ptr [ebp-0A4h]
    L_00463d68:
        or byte ptr [ebp-2C8h],2
    L_00463d6f:
        mov byte ptr [ebp-8Fh],1
    L_00463d76:
        call asm_trandisp2_00463fa7
    L_00463d7b:
        call asm_FUN_00463d83_00463d83
    L_00463d80:
        pop ebx
    L_00463d81:
        leave
    L_00463d82:
        ret
    }
}
