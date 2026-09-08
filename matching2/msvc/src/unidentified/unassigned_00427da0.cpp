#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427DA0..0x00427DB6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427da0() {
    __asm {
    L_00427da0:
        mov eax,dword ptr [edi+4]
    L_00427da3:
        cdq
    L_00427da4:
        idiv esi
    L_00427da6:
        push ebx
    L_00427da7:
        mov ebx,eax
    L_00427da9:
        mov eax,dword ptr [edi]
    L_00427dab:
        cdq
    L_00427dac:
        idiv esi
    L_00427dae:
        mov dword ptr [ecx+4],ebx
    L_00427db1:
        pop ebx
    L_00427db2:
        mov dword ptr [ecx],eax
    L_00427db4:
        mov eax,ecx
    L_00427db6:
        ret
    }
}
