#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004652BB..0x004652D5: Unwind@004652bb
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004652bb_004652bb() {
    __asm {
    L_004652bb:
        push 401FF0h
    L_004652c0:
        push 3
    L_004652c2:
        push 3ACh
    L_004652c7:
        mov eax,dword ptr [ebp+4]
    L_004652ca:
        add eax,1F08h
    L_004652cf:
        push eax
    L_004652d0:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004652d5:
        ret
    }
}
