#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452876..0x0045287A: _atol
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_atol_00452876() {
    __asm {
    L_00452876:
        jmp asm_atol_004527ee
    }
}
