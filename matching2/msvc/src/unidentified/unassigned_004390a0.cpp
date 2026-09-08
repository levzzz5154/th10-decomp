#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004390A0..0x004390DE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004390a0() {
    __asm {
    L_004390a0:
        mov eax,dword ptr [edi+0A000h]
    L_004390a6:
        test eax,eax
    L_004390a8:
        je short L_004390ca
    L_004390aa:
        push esi
    L_004390ab:
        xor esi,esi
    L_004390ad:
        TH10_NOP_LEA_ECX_DISP8()
    L_004390b0:
        mov eax,dword ptr [edi+esi*4]
    L_004390b3:
        test eax,eax
    L_004390b5:
        je short L_004390c0
    L_004390b7:
        push eax
    L_004390b8:
        call asm_free_00452422
    L_004390bd:
        add esp,4
    L_004390c0:
        inc esi
    L_004390c1:
        cmp esi,2800h
    L_004390c7:
        jl short L_004390b0
    L_004390c9:
        pop esi
    L_004390ca:
        test byte ptr [esp+4],1
    L_004390cf:
        je short L_004390da
    L_004390d1:
        push edi
    L_004390d2:
        call asm_free_004524a1
    L_004390d7:
        add esp,4
    L_004390da:
        mov eax,edi
    L_004390dc:
        ret 4
    }
}
