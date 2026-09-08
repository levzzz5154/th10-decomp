#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040584A..0x0040584F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040584a() {
    __asm {
    L_0040584a:
        int 3
    L_0040584b:
        int 3
    L_0040584c:
        int 3
    L_0040584d:
        int 3
    L_0040584e:
        int 3
    L_0040584f:
        int 3
    }
}
