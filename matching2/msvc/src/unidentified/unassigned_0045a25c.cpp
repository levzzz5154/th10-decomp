#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A25C..0x0045A25C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045a25c() {
    __asm {
    L_0045a25c:
        int 3
    }
}
