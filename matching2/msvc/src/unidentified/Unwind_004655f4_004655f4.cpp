#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004655F4..0x0046560E: Unwind@004655f4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004655f4_004655f4() {
    __asm {
    L_004655f4:
        push 401FF0h
    L_004655f9:
        push 5
    L_004655fb:
        push 3ACh
    L_00465600:
        mov eax,dword ptr [ebp+4]
    L_00465603:
        add eax,24D8h
    L_00465608:
        push eax
    L_00465609:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046560e:
        ret
    }
}
