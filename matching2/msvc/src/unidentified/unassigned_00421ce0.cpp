#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CE0..0x00421CE9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421ce0() {
    __asm {
    L_00421ce0:
        mov eax,dword ptr [eax+150h]
    L_00421ce6:
        and eax,1
    L_00421ce9:
        ret
    }
}
