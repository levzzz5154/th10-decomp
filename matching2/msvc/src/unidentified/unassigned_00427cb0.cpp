#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427CB0..0x00427CB5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427cb0() {
    __asm {
    L_00427cb0:
        add word ptr [eax+8],0FFECh
    L_00427cb5:
        ret
    }
}
