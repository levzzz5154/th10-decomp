#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460845..0x00460871: ___shr_12
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_shr_12_00460845() {
    __asm {
    L_00460845:
        mov eax,dword ptr [esp+4]
    L_00460849:
        mov edx,dword ptr [eax+8]
    L_0046084c:
        mov ecx,dword ptr [eax+4]
    L_0046084f:
        push esi
    L_00460850:
        push edi
    L_00460851:
        mov edi,ecx
    L_00460853:
        mov esi,edx
    L_00460855:
        shr ecx,1
    L_00460857:
        shl esi,1Fh
    L_0046085a:
        or ecx,esi
    L_0046085c:
        mov dword ptr [eax+4],ecx
    L_0046085f:
        mov ecx,dword ptr [eax]
    L_00460861:
        shl edi,1Fh
    L_00460864:
        shr ecx,1
    L_00460866:
        or ecx,edi
    L_00460868:
        shr edx,1
    L_0046086a:
        pop edi
    L_0046086b:
        mov dword ptr [eax+8],edx
    L_0046086e:
        mov dword ptr [eax],ecx
    L_00460870:
        pop esi
    L_00460871:
        ret
    }
}
