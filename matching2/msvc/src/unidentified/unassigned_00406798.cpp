#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406798..0x0040679F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
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
