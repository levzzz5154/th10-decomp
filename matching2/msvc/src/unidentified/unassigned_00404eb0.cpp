#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404EB0..0x00404EB8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404eb0() {
    __asm {
    L_00404eb0:
        fld dword ptr [esp+4]
    L_00404eb4:
        fsin
    L_00404eb6:
        ret 4
    }
}
