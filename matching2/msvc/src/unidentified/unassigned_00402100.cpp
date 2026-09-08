#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402100..0x00402104: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402100() {
    __asm {
    L_00402100:
        and dword ptr [eax+30h],0FFFFFFFEh
    L_00402104:
        ret
    }
}
