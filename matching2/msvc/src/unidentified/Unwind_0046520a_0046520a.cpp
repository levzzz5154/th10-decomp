#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046520A..0x00465224: Unwind@0046520a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_0046520a_0046520a() {
    __asm {
    L_0046520a:
        push 401FF0h
    L_0046520f:
        push 14h
    L_00465211:
        push 3ACh
    L_00465216:
        mov eax,dword ptr [ebp+4]
    L_00465219:
        add eax,72DAE4h
    L_0046521e:
        push eax
    L_0046521f:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465224:
        ret
    }
}
