#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC40..0x0041AC71: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ac40() {
    __asm {
    L_0041ac40:
        mov ecx,dword ptr [eax+30h]
    L_0041ac43:
        xor edx,edx
    L_0041ac45:
        test cl,1
    L_0041ac48:
        jne short L_0041ac64
    L_0041ac4a:
        or ecx,1
    L_0041ac4d:
        mov dword ptr [eax+24h],edx
    L_0041ac50:
        mov dword ptr [eax+20h],0FFF0BDC1h
    L_0041ac57:
        mov dword ptr [eax+28h],edx
    L_0041ac5a:
        mov dword ptr [eax+2Ch],476F78h
    L_0041ac61:
        mov dword ptr [eax+30h],ecx
    L_0041ac64:
        mov dword ptr [eax+24h],edx
    L_0041ac67:
        mov dword ptr [eax+28h],edx
    L_0041ac6a:
        mov dword ptr [eax+20h],0FFFFFFFFh
    L_0041ac71:
        ret
    }
}
