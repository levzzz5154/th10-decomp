#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417750..0x00417766: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00417750() {
    __asm {
    L_00417750:
        mov ecx,dword ptr [eax+4]
    L_00417753:
        mov edx,dword ptr [eax+8]
    L_00417756:
        mov dword ptr [ecx+8],edx
    L_00417759:
        mov ecx,dword ptr [eax+8]
    L_0041775c:
        test ecx,ecx
    L_0041775e:
        je short L_00417766
    L_00417760:
        mov eax,dword ptr [eax+4]
    L_00417763:
        mov dword ptr [ecx+4],eax
    L_00417766:
        ret
    }
}
