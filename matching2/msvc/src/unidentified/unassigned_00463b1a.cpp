#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463B1A..0x00463B2B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463b1a() {
    __asm {
    L_00463b1a:
        jmp dword ptr [data_004661d4]
    L_00463b20:
        jmp dword ptr [data_004661d8]
    L_00463b26:
        jmp dword ptr [data_00466184]
    }
}
