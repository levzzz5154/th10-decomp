#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405CC0..0x00405CF2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405cc0() {
    __asm {
    L_00405cc0:
        push edi
    L_00405cc1:
        push 405DE0h
    L_00405cc6:
        push 405D00h
    L_00405ccb:
        push 7D1h
    L_00405cd0:
        push 7F0h
    L_00405cd5:
        lea eax,[esi+60h]
    L_00405cd8:
        push eax
    L_00405cd9:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00405cde:
        xor eax,eax
    L_00405ce0:
        mov ecx,0F82D5h
    L_00405ce5:
        mov edi,esi
    L_00405ce7:
        rep stosd
    L_00405ce9:
        mov dword ptr [data_004776f0],esi
    L_00405cef:
        mov eax,esi
    L_00405cf1:
        pop edi
    L_00405cf2:
        ret
    }
}
