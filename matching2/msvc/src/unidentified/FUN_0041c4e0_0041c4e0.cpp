#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C4E0..0x0041C50D: FUN_0041c4e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c4e0_0041c4e0() {
    __asm {
    L_0041c4e0:
        mov eax,dword ptr [data_00477810]
    L_0041c4e5:
        test byte ptr [eax+58h],4
    L_0041c4e9:
        jne short L_0041c508
    L_0041c4eb:
        mov ecx,dword ptr [ecx+18h]
    L_0041c4ee:
        test ecx,ecx
    L_0041c4f0:
        je short L_0041c508
    L_0041c4f2:
        push esi
    L_0041c4f3:
        cmp dword ptr [ecx+0Ch],1
    L_0041c4f7:
        mov esi,dword ptr [ecx+8]
    L_0041c4fa:
        je short L_0041c501
    L_0041c4fc:
        mov edx,dword ptr [ecx]
    L_0041c4fe:
        call dword ptr [edx+0Ch]
    L_0041c501:
        test esi,esi
    L_0041c503:
        mov ecx,esi
    L_0041c505:
        jne short L_0041c4f3
    L_0041c507:
        pop esi
    L_0041c508:
        mov eax,1
    L_0041c50d:
        ret
    }
}
