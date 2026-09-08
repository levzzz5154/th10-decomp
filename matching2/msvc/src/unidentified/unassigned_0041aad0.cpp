#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AAD0..0x0041AAF6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041aad0() {
    __asm {
    L_0041aad0:
        mov eax,dword ptr [data_00474c7c]
    L_0041aad5:
        lea eax,[eax+eax*2]
    L_0041aad8:
        mov eax,dword ptr [ecx+eax*4+7Ch]
    L_0041aadc:
        test eax,eax
    L_0041aade:
        je short L_0041aaf6
    L_0041aae0:
        mov edx,dword ptr [eax+4]
    L_0041aae3:
        mov eax,dword ptr [eax]
    L_0041aae5:
        mov ecx,dword ptr [eax+70h]
    L_0041aae8:
        test ecx,ecx
    L_0041aaea:
        jle short L_0041aaf0
    L_0041aaec:
        dec ecx
    L_0041aaed:
        mov dword ptr [eax+70h],ecx
    L_0041aaf0:
        test edx,edx
    L_0041aaf2:
        mov eax,edx
    L_0041aaf4:
        jne short L_0041aae0
    L_0041aaf6:
        ret
    }
}
