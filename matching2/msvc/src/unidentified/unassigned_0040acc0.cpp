#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ACC0..0x0040ACC6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040acc0() {
    __asm {
    L_0040acc0:
        movzx eax,word ptr [eax+8]
    L_0040acc4:
        and eax,ecx
    L_0040acc6:
        ret
    }
}
