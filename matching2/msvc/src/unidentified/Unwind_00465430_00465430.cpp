#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465430..0x00465448: Unwind@00465430
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465430_00465430() {
    __asm {
    L_00465430:
        push 401FF0h
    L_00465435:
        push 0Ah
    L_00465437:
        push 3ACh
    L_0046543c:
        mov eax,dword ptr [ebp+4]
    L_0046543f:
        add eax,10h
    L_00465442:
        push eax
    L_00465443:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465448:
        ret
    }
}
