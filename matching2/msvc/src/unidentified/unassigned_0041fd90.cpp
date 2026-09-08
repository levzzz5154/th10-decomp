#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FD90..0x0041FDCE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041fd90() {
    __asm {
    L_0041fd90:
        test byte ptr [edx],2
    L_0041fd93:
        je short L_0041fdc9
    L_0041fd95:
        mov eax,dword ptr [data_004776e0]
    L_0041fd9a:
        mov ecx,dword ptr [eax+0Ch]
    L_0041fd9d:
        or dword ptr [ecx+4],2
    L_0041fda1:
        mov ecx,dword ptr [eax+10h]
    L_0041fda4:
        or dword ptr [ecx+4],2
    L_0041fda8:
        mov eax,dword ptr [eax+89A8h]
    L_0041fdae:
        or dword ptr [eax+4],2
    L_0041fdb2:
        and dword ptr [data_00491ff4],0FFFFEFFFh
    L_0041fdbc:
        mov dword ptr [data_00491fb8],4
    L_0041fdc6:
        and dword ptr [edx],0FFFFFFFDh
    L_0041fdc9:
        mov eax,1
    L_0041fdce:
        ret
    }
}
