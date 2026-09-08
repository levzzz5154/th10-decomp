#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BA4D..0x0041BA4F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ba4d() {
    __asm {
    L_0041ba4d:
        int 3
    L_0041ba4e:
        int 3
    L_0041ba4f:
        int 3
    }
}
