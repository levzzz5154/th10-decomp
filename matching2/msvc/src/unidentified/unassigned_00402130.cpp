#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402130..0x00402134: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402130() {
    __asm {
    L_00402130:
        and dword ptr [eax+20h],0FFFFFFFEh
    L_00402134:
        ret
    }
}
