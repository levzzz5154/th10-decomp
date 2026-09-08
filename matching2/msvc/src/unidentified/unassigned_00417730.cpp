#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417730..0x00417739: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417730() {
    __asm {
    L_00417730:
        fld qword ptr [esp+4]
    L_00417734:
        fst qword ptr [eax+24h]
    L_00417737:
        ret 8
    }
}
