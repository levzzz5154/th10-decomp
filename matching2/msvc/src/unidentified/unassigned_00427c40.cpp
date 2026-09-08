#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427C40..0x00427C43: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427c40() {
    __asm {
    L_00427c40:
        sub dword ptr [eax+30h],ecx
    L_00427c43:
        ret
    }
}
