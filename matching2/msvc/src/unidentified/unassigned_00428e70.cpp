#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428E70..0x00428E7D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428e70() {
    __asm {
    L_00428e70:
        imul eax,98h
    L_00428e76:
        lea eax,[eax+ecx+32D4h]
    L_00428e7d:
        ret
    }
}
