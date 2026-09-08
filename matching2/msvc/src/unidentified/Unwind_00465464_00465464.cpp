#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465464..0x0046547E: Unwind@00465464
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465464_00465464() {
    __asm {
    L_00465464:
        push 401FF0h
    L_00465469:
        push 9
    L_0046546b:
        push 3ACh
    L_00465470:
        mov eax,dword ptr [ebp+4]
    L_00465473:
        add eax,4980h
    L_00465478:
        push eax
    L_00465479:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0046547e:
        ret
    }
}
