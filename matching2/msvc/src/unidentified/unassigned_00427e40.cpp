#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E40..0x00427E4D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427e40() {
    __asm {
    L_00427e40:
        imul eax,98h
    L_00427e46:
        lea eax,[eax+ecx+32DCh]
    L_00427e4d:
        ret
    }
}
