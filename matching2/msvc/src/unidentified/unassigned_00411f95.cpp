#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00411F95..0x00411F97: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00411f95() {
    __asm {
    L_00411f95:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
