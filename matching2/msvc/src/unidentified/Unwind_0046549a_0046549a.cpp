#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046549A..0x004654B4: Unwind@0046549a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046549a_0046549a() {
    __asm {
    L_0046549a:
        push 401FF0h
    L_0046549f:
        push 2
    L_004654a1:
        push 3ACh
    L_004654a6:
        mov eax,dword ptr [ebp+4]
    L_004654a9:
        add eax,793Ch
    L_004654ae:
        push eax
    L_004654af:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004654b4:
        ret
    }
}
