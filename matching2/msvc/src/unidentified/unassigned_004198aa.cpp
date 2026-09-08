#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004198AA..0x004198AF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
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
