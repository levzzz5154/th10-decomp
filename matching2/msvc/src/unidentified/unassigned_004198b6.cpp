#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004198B6..0x004198BF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004198b6() {
    __asm {
    L_004198b6:
        int 3
    L_004198b7:
        int 3
    L_004198b8:
        int 3
    L_004198b9:
        int 3
    L_004198ba:
        int 3
    L_004198bb:
        int 3
    L_004198bc:
        int 3
    L_004198bd:
        int 3
    L_004198be:
        int 3
    L_004198bf:
        int 3
    }
}
