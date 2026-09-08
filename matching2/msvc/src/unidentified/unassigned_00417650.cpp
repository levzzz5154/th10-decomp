#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417650..0x00417655: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417650() {
    __asm {
    L_00417650:
        add eax,340h
    L_00417655:
        ret
    }
}
