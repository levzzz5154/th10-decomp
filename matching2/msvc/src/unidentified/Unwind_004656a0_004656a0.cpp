#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004656A0..0x004656B8: Unwind@004656a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004656a0_004656a0() {
    __asm {
    L_004656a0:
        push 401FF0h
    L_004656a5:
        push 0Ah
    L_004656a7:
        push 3ACh
    L_004656ac:
        mov eax,dword ptr [ebp+4]
    L_004656af:
        add eax,10h
    L_004656b2:
        push eax
    L_004656b3:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004656b8:
        ret
    }
}
