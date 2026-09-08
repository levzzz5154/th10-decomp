#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CD0..0x00421CD7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421cd0() {
    __asm {
    L_00421cd0:
        movzx eax,byte ptr [eax+13Dh]
    L_00421cd7:
        ret
    }
}
