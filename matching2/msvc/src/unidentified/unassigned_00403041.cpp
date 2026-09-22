#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403041..0x0040304F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2801): closest_byte_count=0/15; first_diff=extent mismatch
// (readable empty function emitted 1 byte); residual_class=pure INT3
// alignment/padding, not a C++ function; variants_tested=empty extern-C
// cdecl function; next_lever=none without non-readable byte/padding
// representation.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00403041() {
    __asm {
    L_00403041:
        int 3
    L_00403042:
        int 3
    L_00403043:
        int 3
    L_00403044:
        int 3
    L_00403045:
        int 3
    L_00403046:
        int 3
    L_00403047:
        int 3
    L_00403048:
        int 3
    L_00403049:
        int 3
    L_0040304a:
        int 3
    L_0040304b:
        int 3
    L_0040304c:
        int 3
    L_0040304d:
        int 3
    L_0040304e:
        int 3
    L_0040304f:
        int 3
    }
}
