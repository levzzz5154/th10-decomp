#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C00..0x00434C00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434c00() {
    __asm {
    L_00434c00:
        ret
    }
}
