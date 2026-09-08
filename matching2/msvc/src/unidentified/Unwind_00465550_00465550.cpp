#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465550..0x0046556A: Unwind@00465550
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465550_00465550() {
    __asm {
    L_00465550:
        push 401FF0h
    L_00465555:
        push 8
    L_00465557:
        push 3ACh
    L_0046555c:
        mov eax,dword ptr [ebp+4]
    L_0046555f:
        add eax,180h
    L_00465564:
        push eax
    L_00465565:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046556a:
        ret
    }
}
