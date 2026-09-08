#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041ACB0..0x0041ACE5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041acb0() {
    __asm {
    L_0041acb0:
        push edi
    L_0041acb1:
        push 41AD60h
    L_0041acb6:
        push 41ACF0h
    L_0041acbb:
        push 896h
    L_0041acc0:
        push 3F0h
    L_0041acc5:
        lea eax,[esi+14h]
    L_0041acc8:
        push eax
    L_0041acc9:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0041acce:
        xor eax,eax
    L_0041acd0:
        mov ecx,873B0h
    L_0041acd5:
        mov edi,esi
    L_0041acd7:
        rep stosd
    L_0041acd9:
        or dword ptr [esi],2
    L_0041acdc:
        mov dword ptr [data_00477818],esi
    L_0041ace2:
        mov eax,esi
    L_0041ace4:
        pop edi
    L_0041ace5:
        ret
    }
}
