#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A00..0x00465A13: FUN_00465a00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a00_00465a00() {
    __asm {
    L_00465a00:
        push 434C20h
    L_00465a05:
        push 14h
    L_00465a07:
        push 10h
    L_00465a09:
        push 4923B0h
    L_00465a0e:
        call asm_eh_vector_destructor_iterator_004525ff
    L_00465a13:
        ret
    }
}
