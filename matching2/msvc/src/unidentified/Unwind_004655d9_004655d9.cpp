#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004655D9..0x004655F3: Unwind@004655d9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004655d9_004655d9() {
    __asm {
    L_004655d9:
        push 401FF0h
    L_004655de:
        push 8
    L_004655e0:
        push 3ACh
    L_004655e5:
        mov eax,dword ptr [ebp+4]
    L_004655e8:
        add eax,778h
    L_004655ed:
        push eax
    L_004655ee:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004655f3:
        ret
    }
}
