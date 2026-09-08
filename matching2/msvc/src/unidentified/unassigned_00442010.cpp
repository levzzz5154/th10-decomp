#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442010..0x00442041: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00442010() {
    __asm {
    L_00442010:
        mov ecx,dword ptr [eax+20h]
    L_00442013:
        xor edx,edx
    L_00442015:
        test cl,1
    L_00442018:
        jne short L_00442034
    L_0044201a:
        or ecx,1
    L_0044201d:
        mov dword ptr [eax+14h],edx
    L_00442020:
        mov dword ptr [eax+10h],0FFF0BDC1h
    L_00442027:
        mov dword ptr [eax+18h],edx
    L_0044202a:
        mov dword ptr [eax+1Ch],476F78h
    L_00442031:
        mov dword ptr [eax+20h],ecx
    L_00442034:
        mov dword ptr [eax+14h],edx
    L_00442037:
        mov dword ptr [eax+18h],edx
    L_0044203a:
        mov dword ptr [eax+10h],0FFFFFFFFh
    L_00442041:
        ret
    }
}
