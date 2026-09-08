#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C930..0x0043C968: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043c930() {
    __asm {
    L_0043c930:
        mov dword ptr [eax+2Ch],1
    L_0043c937:
        mov ecx,dword ptr [eax+40h]
    L_0043c93a:
        xor edx,edx
    L_0043c93c:
        test cl,1
    L_0043c93f:
        jne short L_0043c95b
    L_0043c941:
        or ecx,1
    L_0043c944:
        mov dword ptr [eax+34h],edx
    L_0043c947:
        mov dword ptr [eax+30h],0FFF0BDC1h
    L_0043c94e:
        mov dword ptr [eax+38h],edx
    L_0043c951:
        mov dword ptr [eax+3Ch],476F78h
    L_0043c958:
        mov dword ptr [eax+40h],ecx
    L_0043c95b:
        mov dword ptr [eax+34h],edx
    L_0043c95e:
        mov dword ptr [eax+38h],edx
    L_0043c961:
        mov dword ptr [eax+30h],0FFFFFFFFh
    L_0043c968:
        ret
    }
}
