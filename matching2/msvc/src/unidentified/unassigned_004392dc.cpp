#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004392DC..0x004392DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004392dc() {
    __asm {
    L_004392dc:
        int 3
    L_004392dd:
        int 3
    L_004392de:
        int 3
    L_004392df:
        int 3
    }
}
