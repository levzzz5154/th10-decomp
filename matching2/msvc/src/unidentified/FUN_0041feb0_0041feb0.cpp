#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FEB0..0x0041FEEE: FUN_0041feb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041feb0_0041feb0() {
    __asm {
    L_0041feb0:
        test byte ptr [ecx],2
    L_0041feb3:
        je short L_0041fee9
    L_0041feb5:
        mov eax,dword ptr [data_004776e0]
    L_0041feba:
        mov edx,dword ptr [eax+0Ch]
    L_0041febd:
        or dword ptr [edx+4],2
    L_0041fec1:
        mov edx,dword ptr [eax+10h]
    L_0041fec4:
        or dword ptr [edx+4],2
    L_0041fec8:
        mov eax,dword ptr [eax+89A8h]
    L_0041fece:
        or dword ptr [eax+4],2
    L_0041fed2:
        and dword ptr [data_00491ff4],0FFFFEFFFh
    L_0041fedc:
        mov dword ptr [data_00491fb8],4
    L_0041fee6:
        and dword ptr [ecx],0FFFFFFFDh
    L_0041fee9:
        mov eax,1
    L_0041feee:
        ret
    }
}
