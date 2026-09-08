#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E760..0x0040E76A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040e760() {
    __asm {
    L_0040e760:
        add ecx,103Ch
    L_0040e766:
        jmp asm_FUN_0040e770_0040e770
    }
}
