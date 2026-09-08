#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412EB0..0x00412EB8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412eb0() {
    __asm {
    L_00412eb0:
        fld dword ptr [eax+10h]
    L_00412eb3:
        fld dword ptr [eax+0Ch]
    L_00412eb6:
        fpatan
    L_00412eb8:
        ret
    }
}
