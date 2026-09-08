#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401517..0x0040151F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401517() {
    __asm {
    L_00401517:
        int 3
    L_00401518:
        int 3
    L_00401519:
        int 3
    L_0040151a:
        int 3
    L_0040151b:
        int 3
    L_0040151c:
        int 3
    L_0040151d:
        int 3
    L_0040151e:
        int 3
    L_0040151f:
        int 3
    }
}
