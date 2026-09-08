#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004367D0..0x004367D4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004367d0() {
    __asm {
    L_004367d0:
        jmp asm_memmove_00453280
    }
}
