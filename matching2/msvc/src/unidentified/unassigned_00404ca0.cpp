#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404CA0..0x00404CD7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404ca0() {
    __asm {
    L_00404ca0:
        mov ecx,dword ptr [eax+80h]
    L_00404ca6:
        xor edx,edx
    L_00404ca8:
        test cl,1
    L_00404cab:
        jne short L_00404cca
    L_00404cad:
        or ecx,1
    L_00404cb0:
        mov dword ptr [eax+74h],edx
    L_00404cb3:
        mov dword ptr [eax+70h],0FFF0BDC1h
    L_00404cba:
        mov dword ptr [eax+78h],edx
    L_00404cbd:
        mov dword ptr [eax+7Ch],476F78h
    L_00404cc4:
        mov dword ptr [eax+80h],ecx
    L_00404cca:
        mov dword ptr [eax+74h],edx
    L_00404ccd:
        mov dword ptr [eax+78h],edx
    L_00404cd0:
        mov dword ptr [eax+70h],0FFFFFFFFh
    L_00404cd7:
        ret
    }
}
