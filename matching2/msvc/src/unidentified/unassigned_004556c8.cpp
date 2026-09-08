#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004556C8..0x004556DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004556c8() {
    __asm {
    L_004556c8:
        call asm_getptd_00456357
    L_004556cd:
        cmp dword ptr [eax+70h],0
    L_004556d1:
        je short L_004556db
    L_004556d3:
        call asm_getptd_00456357
    L_004556d8:
        call dword ptr [eax+70h]
    L_004556db:
        jmp asm_terminate_00455693
    }
}
