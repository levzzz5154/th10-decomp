#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428E80..0x00428E8D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00428e80() {
    __asm {
    L_00428e80:
        imul eax,98h
    L_00428e86:
        lea eax,[eax+ecx+32E4h]
    L_00428e8d:
        ret
    }
}
