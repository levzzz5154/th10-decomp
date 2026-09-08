#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465250..0x00465267: Unwind@00465250
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_00465250_00465250() {
    __asm {
    L_00465250:
        push 42AC60h
    L_00465255:
        push 8
    L_00465257:
        push 24h
    L_00465259:
        mov eax,dword ptr [ebp+4]
    L_0046525c:
        add eax,0A0h
    L_00465261:
        push eax
    L_00465262:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465267:
        ret
    }
}
