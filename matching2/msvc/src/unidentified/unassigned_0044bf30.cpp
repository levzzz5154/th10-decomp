#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BF30..0x0044BF3D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bf30() {
    __asm {
    L_0044bf30:
        mov eax,dword ptr [ecx+0Ch]
    L_0044bf33:
        test eax,eax
    L_0044bf35:
        je short L_0044bf3a
    L_0044bf37:
        dec dword ptr [eax+4]
    L_0044bf3a:
        mov dword ptr [ecx+0Ch],edx
    L_0044bf3d:
        ret
    }
}
