#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465520..0x0046553B: Unwind@00465520
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465520_00465520() {
    __asm {
    L_00465520:
        push 405DE0h
    L_00465525:
        push 7D1h
    L_0046552a:
        push 7F0h
    L_0046552f:
        mov eax,dword ptr [ebp+4]
    L_00465532:
        add eax,60h
    L_00465535:
        push eax
    L_00465536:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046553b:
        ret
    }
}
