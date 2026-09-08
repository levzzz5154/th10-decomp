#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438850..0x00438853: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438850() {
    __asm {
    L_00438850:
        or eax,0FFFFFFFFh
    L_00438853:
        ret
    }
}
