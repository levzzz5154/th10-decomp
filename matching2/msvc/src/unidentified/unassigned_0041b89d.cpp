#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041B89D..0x0041B89F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041b89d() {
    __asm {
    L_0041b89d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
