#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CC0..0x00421CCB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421cc0() {
    __asm {
    L_00421cc0:
        mov eax,dword ptr [eax+150h]
    L_00421cc6:
        shr eax,1
    L_00421cc8:
        and eax,1
    L_00421ccb:
        ret
    }
}
