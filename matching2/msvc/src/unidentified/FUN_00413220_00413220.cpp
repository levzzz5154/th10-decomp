#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413220..0x00413230: FUN_00413220
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413220_00413220() {
    __asm {
    L_00413220:
        mov edx,dword ptr [eax]
    L_00413222:
        mov dword ptr [ecx],edx
    L_00413224:
        mov edx,dword ptr [eax+4]
    L_00413227:
        mov dword ptr [ecx+4],edx
    L_0041322a:
        mov eax,dword ptr [eax+8]
    L_0041322d:
        mov dword ptr [ecx+8],eax
    L_00413230:
        ret
    }
}
