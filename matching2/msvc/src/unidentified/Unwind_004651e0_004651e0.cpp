#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004651E0..0x004651FB: Unwind@004651e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004651e0_004651e0() {
    __asm {
    L_004651e0:
        push 401FF0h
    L_004651e5:
        push 1000h
    L_004651ea:
        push 3ACh
    L_004651ef:
        mov eax,dword ptr [ebp+4]
    L_004651f2:
        add eax,68h
    L_004651f5:
        push eax
    L_004651f6:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004651fb:
        ret
    }
}
