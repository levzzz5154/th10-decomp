#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438860..0x00438869: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438860() {
    __asm {
    L_00438860:
        push eax
    L_00438861:
        call asm_operator_new_00452493
    L_00438866:
        add esp,4
    L_00438869:
        ret
    }
}
