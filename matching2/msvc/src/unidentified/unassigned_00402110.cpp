#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402110..0x00402114: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402110() {
    __asm {
    L_00402110:
        and dword ptr [eax+40h],0FFFFFFFEh
    L_00402114:
        ret
    }
}
