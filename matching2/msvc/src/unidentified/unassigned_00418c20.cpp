#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418C20..0x00418C20: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418c20() {
    __asm {
    L_00418c20:
        ret
    }
}
