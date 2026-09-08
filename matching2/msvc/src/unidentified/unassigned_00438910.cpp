#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438910..0x0043893A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438910() {
    __asm {
    L_00438910:
        mov eax,dword ptr [edi+0A000h]
    L_00438916:
        test eax,eax
    L_00438918:
        je short L_0043893a
    L_0043891a:
        push esi
    L_0043891b:
        xor esi,esi
    L_0043891d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00438920:
        mov eax,dword ptr [edi+esi*4]
    L_00438923:
        test eax,eax
    L_00438925:
        je short L_00438930
    L_00438927:
        push eax
    L_00438928:
        call asm_free_00452422
    L_0043892d:
        add esp,4
    L_00438930:
        inc esi
    L_00438931:
        cmp esi,2800h
    L_00438937:
        jl short L_00438920
    L_00438939:
        pop esi
    L_0043893a:
        ret
    }
}
