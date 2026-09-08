#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F3A3..0x0045F3A3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045f3a3() {
    __asm {
    L_0045f3a3:
        int 3
    }
}
