#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F90..0x00412F93: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412f90() {
    __asm {
    L_00412f90:
        fld dword ptr [eax+1Ch]
    L_00412f93:
        ret
    }
}
