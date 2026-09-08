#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422A9A..0x00422A9F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00422a9a() {
    __asm {
    L_00422a9a:
        int 3
    L_00422a9b:
        int 3
    L_00422a9c:
        int 3
    L_00422a9d:
        int 3
    L_00422a9e:
        int 3
    L_00422a9f:
        int 3
    }
}
