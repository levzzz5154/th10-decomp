#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422AA7..0x00422AAF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00422aa7() {
    __asm {
    L_00422aa7:
        int 3
    L_00422aa8:
        int 3
    L_00422aa9:
        int 3
    L_00422aaa:
        int 3
    L_00422aab:
        int 3
    L_00422aac:
        int 3
    L_00422aad:
        int 3
    L_00422aae:
        int 3
    L_00422aaf:
        int 3
    }
}
