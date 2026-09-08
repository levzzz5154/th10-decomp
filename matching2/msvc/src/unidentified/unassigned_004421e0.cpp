#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004421E0..0x00442211: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004421e0() {
    __asm {
    L_004421e0:
        mov ecx,dword ptr [eax+40h]
    L_004421e3:
        xor edx,edx
    L_004421e5:
        test cl,1
    L_004421e8:
        jne short L_00442204
    L_004421ea:
        or ecx,1
    L_004421ed:
        mov dword ptr [eax+34h],edx
    L_004421f0:
        mov dword ptr [eax+30h],0FFF0BDC1h
    L_004421f7:
        mov dword ptr [eax+38h],edx
    L_004421fa:
        mov dword ptr [eax+3Ch],476F78h
    L_00442201:
        mov dword ptr [eax+40h],ecx
    L_00442204:
        mov dword ptr [eax+34h],edx
    L_00442207:
        mov dword ptr [eax+38h],edx
    L_0044220a:
        mov dword ptr [eax+30h],0FFFFFFFFh
    L_00442211:
        ret
    }
}
