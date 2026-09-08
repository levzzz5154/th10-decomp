#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413120..0x00413133: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413120() {
    __asm {
    L_00413120:
        mov edx,dword ptr [eax]
    L_00413122:
        add ecx,0Ch
    L_00413125:
        mov dword ptr [ecx],edx
    L_00413127:
        mov edx,dword ptr [eax+4]
    L_0041312a:
        mov dword ptr [ecx+4],edx
    L_0041312d:
        mov eax,dword ptr [eax+8]
    L_00413130:
        mov dword ptr [ecx+8],eax
    L_00413133:
        ret
    }
}
