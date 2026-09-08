#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418CC0..0x00418CFE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418cc0() {
    __asm {
    L_00418cc0:
        mov ecx,dword ptr [eax+24h]
    L_00418cc3:
        and ecx,0FFFFFFFEh
    L_00418cc6:
        xor edx,edx
    L_00418cc8:
        test cl,1
    L_00418ccb:
        mov dword ptr [eax+24h],ecx
    L_00418cce:
        jne short L_00418cea
    L_00418cd0:
        or ecx,1
    L_00418cd3:
        mov dword ptr [eax+18h],edx
    L_00418cd6:
        mov dword ptr [eax+14h],0FFF0BDC1h
    L_00418cdd:
        mov dword ptr [eax+1Ch],edx
    L_00418ce0:
        mov dword ptr [eax+20h],476F78h
    L_00418ce7:
        mov dword ptr [eax+24h],ecx
    L_00418cea:
        mov dword ptr [eax+18h],edx
    L_00418ced:
        mov dword ptr [eax+1Ch],edx
    L_00418cf0:
        mov dword ptr [eax+14h],0FFFFFFFFh
    L_00418cf7:
        mov dword ptr [eax+34h],1
    L_00418cfe:
        ret
    }
}
