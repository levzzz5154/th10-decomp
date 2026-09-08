#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428E90..0x00428E9D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428e90() {
    __asm {
    L_00428e90:
        imul eax,98h
    L_00428e96:
        lea eax,[eax+ecx+32ECh]
    L_00428e9d:
        ret
    }
}
