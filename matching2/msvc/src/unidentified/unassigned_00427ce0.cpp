#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427CE0..0x00427CFD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427ce0() {
    __asm {
    L_00427ce0:
        fild dword ptr [ecx]
    L_00427ce2:
        fmul dword ptr [data_00470b00]
    L_00427ce8:
        fstp dword ptr [eax]
    L_00427cea:
        fild dword ptr [ecx+4]
    L_00427ced:
        mov dword ptr [eax+8],0
    L_00427cf4:
        fmul dword ptr [data_00470b00]
    L_00427cfa:
        fstp dword ptr [eax+4]
    L_00427cfd:
        ret
    }
}
