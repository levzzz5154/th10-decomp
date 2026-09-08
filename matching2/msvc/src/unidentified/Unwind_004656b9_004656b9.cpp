#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004656B9..0x004656D3: Unwind@004656b9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004656b9_004656b9() {
    __asm {
    L_004656b9:
        push 401FF0h
    L_004656be:
        push 0Ah
    L_004656c0:
        push 3ACh
    L_004656c5:
        mov eax,dword ptr [ebp+4]
    L_004656c8:
        add eax,24C8h
    L_004656cd:
        push eax
    L_004656ce:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004656d3:
        ret
    }
}
