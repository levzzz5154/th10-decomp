#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417720..0x00417729: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417720() {
    __asm {
    L_00417720:
        add eax,9E14h
    L_00417725:
        jmp asm_FUN_00409e50_00409e50
    }
}
