#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046547F..0x00465499: Unwind@0046547f
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046547f_0046547f() {
    __asm {
    L_0046547f:
        push 401FF0h
    L_00465484:
        push 4
    L_00465486:
        push 3ACh
    L_0046548b:
        mov eax,dword ptr [ebp+4]
    L_0046548e:
        add eax,6A8Ch
    L_00465493:
        push eax
    L_00465494:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465499:
        ret
    }
}
