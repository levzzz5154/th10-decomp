#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C530..0x0040C535: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c530() {
    __asm {
    L_0040c530:
        movzx eax,word ptr [eax]
    L_0040c533:
        and eax,ecx
    L_0040c535:
        ret
    }
}
