#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040150A..0x0040150F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040150a() {
    __asm {
    L_0040150a:
        int 3
    L_0040150b:
        int 3
    L_0040150c:
        int 3
    L_0040150d:
        int 3
    L_0040150e:
        int 3
    L_0040150f:
        int 3
    }
}
