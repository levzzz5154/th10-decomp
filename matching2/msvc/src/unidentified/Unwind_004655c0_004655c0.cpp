#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004655C0..0x004655D8: Unwind@004655c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004655c0_004655c0() {
    __asm {
    L_004655c0:
        push 401FF0h
    L_004655c5:
        push 2
    L_004655c7:
        push 3ACh
    L_004655cc:
        mov eax,dword ptr [ebp+4]
    L_004655cf:
        add eax,10h
    L_004655d2:
        push eax
    L_004655d3:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004655d8:
        ret
    }
}
