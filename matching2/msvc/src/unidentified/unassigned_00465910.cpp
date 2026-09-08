#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465910..0x00465933: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465910() {
    __asm {
    L_00465910:
        push 434C20h
    L_00465915:
        push 434C10h
    L_0046591a:
        push 14h
    L_0046591c:
        push 10h
    L_0046591e:
        push 4923B0h
    L_00465923:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00465928:
        push 465A00h
    L_0046592d:
        call asm_atexit_00452e0a
    L_00465932:
        pop ecx
    L_00465933:
        ret
    }
}
