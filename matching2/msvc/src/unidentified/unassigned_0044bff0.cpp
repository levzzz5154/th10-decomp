#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BFF0..0x0044BFF5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bff0() {
    __asm {
    L_0044bff0:
        mov ecx,dword ptr [eax+0Ch]
    L_0044bff3:
        fld dword ptr [ecx]
    L_0044bff5:
        ret
    }
}
