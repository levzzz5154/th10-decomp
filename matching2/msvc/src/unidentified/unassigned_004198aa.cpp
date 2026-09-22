#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004198AA..0x004198AF: six-byte INT3 alignment span; Ghidra reports no
// function boundary, callers, callees, xrefs, or dataflow at this address.
// BLOCKED: closest_byte_count=0/6; first_diff=extent mismatch; residual_class=
// pure INT3 alignment/padding; variants_tested=readable empty extern-C cdecl
// function (compiled extent 1 byte); next_lever=none without a non-readable
// padding representation.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004198aa() {
    __asm {
    L_004198aa:
        int 3
    L_004198ab:
        int 3
    L_004198ac:
        int 3
    L_004198ad:
        int 3
    L_004198ae:
        int 3
    L_004198af:
        int 3
    }
}
