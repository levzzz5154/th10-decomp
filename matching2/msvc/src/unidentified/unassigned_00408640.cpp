#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408640..0x00408653: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408640() {
    __asm {
    L_00408640:
        fld dword ptr [eax+4]
    L_00408643:
        fld dword ptr [eax]
    L_00408645:
        fld st(0)
    L_00408647:
        fmul st,st(1)
    L_00408649:
        fld st(2)
    L_0040864b:
        fmul st,st(3)
    L_0040864d:
        faddp st(1),st
    L_0040864f:
        fstp st(2)
    L_00408651:
        fstp st(0)
    L_00408653:
        ret
    }
}
