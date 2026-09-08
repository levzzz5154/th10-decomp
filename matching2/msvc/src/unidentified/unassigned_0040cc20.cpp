#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CC20..0x0040CC25: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cc20() {
    __asm {
    L_0040cc20:
        add eax,13C0h
    L_0040cc25:
        ret
    }
}
