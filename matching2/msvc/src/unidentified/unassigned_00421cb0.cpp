#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421CB0..0x00421CBC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421cb0() {
    __asm {
    L_00421cb0:
        mov eax,dword ptr [eax+150h]
    L_00421cb6:
        shr eax,3
    L_00421cb9:
        and eax,1
    L_00421cbc:
        ret
    }
}
