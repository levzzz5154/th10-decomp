#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418B30..0x00418B38: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418b30() {
    __asm {
    L_00418b30:
        mov eax,dword ptr [eax+60h]
    L_00418b33:
        shr eax,1
    L_00418b35:
        and eax,1
    L_00418b38:
        ret
    }
}
