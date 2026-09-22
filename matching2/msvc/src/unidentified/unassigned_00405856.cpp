#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405856..0x0040585F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2801): closest_byte_count=0/10; first_diff=extent mismatch
// (readable empty function emitted 1 byte); residual_class=pure INT3
// alignment/padding, not a C++ function; variants_tested=empty extern-C
// cdecl function; next_lever=none without non-readable byte/padding
// representation.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405856() {
    __asm {
    L_00405856:
        int 3
    L_00405857:
        int 3
    L_00405858:
        int 3
    L_00405859:
        int 3
    L_0040585a:
        int 3
    L_0040585b:
        int 3
    L_0040585c:
        int 3
    L_0040585d:
        int 3
    L_0040585e:
        int 3
    L_0040585f:
        int 3
    }
}
