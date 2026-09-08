#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004654E0..0x004654F8: Unwind@004654e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004654e0_004654e0() {
    __asm {
    L_004654e0:
        push 401FF0h
    L_004654e5:
        push 2
    L_004654e7:
        push 3ACh
    L_004654ec:
        mov eax,dword ptr [ebp+4]
    L_004654ef:
        add eax,10h
    L_004654f2:
        push eax
    L_004654f3:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004654f8:
        ret
    }
}
