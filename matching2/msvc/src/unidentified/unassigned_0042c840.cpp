#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C840..0x0042C848: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c840() {
    __asm {
    L_0042c840:
        movsx eax,byte ptr [ecx+eax+1D888h]
    L_0042c848:
        ret
    }
}
