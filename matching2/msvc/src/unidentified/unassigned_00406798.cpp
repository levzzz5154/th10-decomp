#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406798..0x0040679F: eight-byte INT3 alignment span; Ghidra reports no
// function boundary, callers, callees, xrefs, or dataflow at this address.
// BLOCKED: closest_byte_count=0/8; first_diff=extent mismatch; residual_class=
// pure INT3 alignment/padding; variants_tested=readable empty extern-C cdecl
// function (compiled extent 1 byte); next_lever=none without a non-readable
// padding representation.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00406798() {
    __asm {
    L_00406798:
        int 3
    L_00406799:
        int 3
    L_0040679a:
        int 3
    L_0040679b:
        int 3
    L_0040679c:
        int 3
    L_0040679d:
        int 3
    L_0040679e:
        int 3
    L_0040679f:
        int 3
    }
}
