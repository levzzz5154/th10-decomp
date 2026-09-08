#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418EC0..0x00418EDB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418ec0() {
    __asm {
    L_00418ec0:
        mov ecx,dword ptr [eax+8]
    L_00418ec3:
        test ecx,ecx
    L_00418ec5:
        mov edx,2
    L_00418eca:
        je short L_00418ecf
    L_00418ecc:
        or dword ptr [ecx+4],edx
    L_00418ecf:
        mov ecx,dword ptr [eax+0Ch]
    L_00418ed2:
        test ecx,ecx
    L_00418ed4:
        je short L_00418edb
    L_00418ed6:
        mov eax,ecx
    L_00418ed8:
        or dword ptr [eax+4],edx
    L_00418edb:
        ret
    }
}
