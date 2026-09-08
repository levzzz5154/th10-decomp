#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412750..0x00412787: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412750() {
    __asm {
    L_00412750:
        mov eax,edx
    L_00412752:
        shl eax,4
    L_00412755:
        add eax,esi
    L_00412757:
        test ecx,ecx
    L_00412759:
        mov dword ptr [eax+2494h],ecx
    L_0041275f:
        jl short L_00412785
    L_00412761:
        mov ecx,dword ptr [esp+4]
    L_00412765:
        mov dword ptr [eax+2498h],ecx
    L_0041276b:
        mov ecx,dword ptr [esp+8]
    L_0041276f:
        add edx,24Ah
    L_00412775:
        mov dword ptr [eax+249Ch],ecx
    L_0041277b:
        mov eax,dword ptr [esp+0Ch]
    L_0041277f:
        shl edx,4
    L_00412782:
        mov dword ptr [edx+esi],eax
    L_00412785:
        ret 0Ch
    }
}
