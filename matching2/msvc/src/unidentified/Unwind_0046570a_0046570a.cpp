#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046570A..0x00465724: Unwind@0046570a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046570a_0046570a() {
    __asm {
    L_0046570a:
        push 401FF0h
    L_0046570f:
        push 2
    L_00465711:
        push 3ACh
    L_00465716:
        mov eax,dword ptr [ebp+4]
    L_00465719:
        add eax,793Ch
    L_0046571e:
        push eax
    L_0046571f:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465724:
        ret
    }
}
