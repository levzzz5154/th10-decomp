#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417740..0x00417749: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417740() {
    __asm {
    L_00417740:
        fld qword ptr [esp+4]
    L_00417744:
        fst qword ptr [eax+2Ch]
    L_00417747:
        ret 8
    }
}
