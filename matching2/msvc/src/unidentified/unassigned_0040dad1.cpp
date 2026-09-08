#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040DAD1..0x0040DADF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040dad1() {
    __asm {
    L_0040dad1:
        int 3
    L_0040dad2:
        int 3
    L_0040dad3:
        int 3
    L_0040dad4:
        int 3
    L_0040dad5:
        int 3
    L_0040dad6:
        int 3
    L_0040dad7:
        int 3
    L_0040dad8:
        int 3
    L_0040dad9:
        int 3
    L_0040dada:
        int 3
    L_0040dadb:
        int 3
    L_0040dadc:
        int 3
    L_0040dadd:
        int 3
    L_0040dade:
        int 3
    L_0040dadf:
        int 3
    }
}
