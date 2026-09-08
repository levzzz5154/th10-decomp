#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004656D4..0x004656EE: Unwind@004656d4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004656d4_004656d4() {
    __asm {
    L_004656d4:
        push 401FF0h
    L_004656d9:
        push 9
    L_004656db:
        push 3ACh
    L_004656e0:
        mov eax,dword ptr [ebp+4]
    L_004656e3:
        add eax,4980h
    L_004656e8:
        push eax
    L_004656e9:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004656ee:
        ret
    }
}
