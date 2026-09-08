#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004656EF..0x00465709: Unwind@004656ef
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004656ef_004656ef() {
    __asm {
    L_004656ef:
        push 401FF0h
    L_004656f4:
        push 4
    L_004656f6:
        push 3ACh
    L_004656fb:
        mov eax,dword ptr [ebp+4]
    L_004656fe:
        add eax,6A8Ch
    L_00465703:
        push eax
    L_00465704:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465709:
        ret
    }
}
