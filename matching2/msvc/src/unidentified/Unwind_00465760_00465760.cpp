#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465760..0x0046577B: Unwind@00465760
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465760_00465760() {
    __asm {
    L_00465760:
        push 401FF0h
    L_00465765:
        push 1000h
    L_0046576a:
        push 3ACh
    L_0046576f:
        mov eax,dword ptr [ebp+4]
    L_00465772:
        add eax,68h
    L_00465775:
        push eax
    L_00465776:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046577b:
        ret
    }
}
