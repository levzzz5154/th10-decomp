#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ACD0..0x0040ACD6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040acd0() {
    __asm {
    L_0040acd0:
        movzx eax,word ptr [eax+6]
    L_0040acd4:
        and eax,ecx
    L_0040acd6:
        ret
    }
}
