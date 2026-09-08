#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046578A..0x004657A4: Unwind@0046578a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046578a_0046578a() {
    __asm {
    L_0046578a:
        push 401FF0h
    L_0046578f:
        push 14h
    L_00465791:
        push 3ACh
    L_00465796:
        mov eax,dword ptr [ebp+4]
    L_00465799:
        add eax,72DAE4h
    L_0046579e:
        push eax
    L_0046579f:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004657a4:
        ret
    }
}
