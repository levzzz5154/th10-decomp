#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004088A0..0x004088AA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004088a0() {
    __asm {
    L_004088a0:
        imul eax,437Ch
    L_004088a6:
        lea eax,[eax+ecx+8]
    L_004088aa:
        ret
    }
}
