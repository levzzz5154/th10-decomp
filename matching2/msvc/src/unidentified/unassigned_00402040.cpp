#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402040..0x00402047: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402040() {
    __asm {
    L_00402040:
        push eax
    L_00402041:
        call asm_free_00452422
    L_00402046:
        pop ecx
    L_00402047:
        ret
    }
}
