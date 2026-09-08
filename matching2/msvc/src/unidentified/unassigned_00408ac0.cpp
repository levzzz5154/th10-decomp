#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408AC0..0x00408AE2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408ac0() {
    __asm {
    L_00408ac0:
        mov ecx,dword ptr [eax+8]
    L_00408ac3:
        test ecx,ecx
    L_00408ac5:
        mov edx,2
    L_00408aca:
        je short L_00408acf
    L_00408acc:
        or dword ptr [ecx+4],edx
    L_00408acf:
        mov ecx,dword ptr [eax+0Ch]
    L_00408ad2:
        test ecx,ecx
    L_00408ad4:
        je short L_00408ad9
    L_00408ad6:
        or dword ptr [ecx+4],edx
    L_00408ad9:
        mov eax,dword ptr [eax+37ACh]
    L_00408adf:
        or dword ptr [eax+4],edx
    L_00408ae2:
        ret
    }
}
