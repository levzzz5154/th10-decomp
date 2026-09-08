#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004067A0..0x004067CB: FUN_004067a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004067a0_004067a0() {
    __asm {
    L_004067a0:
        mov eax,dword ptr [data_00477810]
    L_004067a5:
        test eax,eax
    L_004067a7:
        push edi
    L_004067a8:
        mov edi,ecx
    L_004067aa:
        je short L_004067b2
    L_004067ac:
        test byte ptr [eax+58h],4
    L_004067b0:
        jne short L_004067c5
    L_004067b2:
        push esi
    L_004067b3:
        xor esi,esi
    L_004067b5:
        mov ecx,esi
    L_004067b7:
        mov eax,edi
    L_004067b9:
        call asm_FUN_004066e0_004066e0
    L_004067be:
        inc esi
    L_004067bf:
        cmp esi,6
    L_004067c2:
        jl short L_004067b5
    L_004067c4:
        pop esi
    L_004067c5:
        mov eax,1
    L_004067ca:
        pop edi
    L_004067cb:
        ret
    }
}
