#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412EA0..0x00412EA7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412ea0() {
    __asm {
    L_00412ea0:
        movsx eax,word ptr [eax+38Ah]
    L_00412ea7:
        ret
    }
}
