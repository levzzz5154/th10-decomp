#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C880..0x0041C8B5: FUN_0041c880
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c880_0041c880() {
    __asm {
    L_0041c880:
        mov ecx,dword ptr [eax+18h]
    L_0041c883:
        push ebp
    L_0041c884:
        mov ebp,dword ptr [esp+8]
    L_0041c888:
        push edi
    L_0041c889:
        xor edi,edi
    L_0041c88b:
        test ecx,ecx
    L_0041c88d:
        je short L_0041c8af
    L_0041c88f:
        push ebx
    L_0041c890:
        mov ebx,dword ptr [esp+14h]
    L_0041c894:
        push esi
    L_0041c895:
        cmp dword ptr [ecx+0Ch],1
    L_0041c899:
        mov esi,dword ptr [ecx+8]
    L_0041c89c:
        je short L_0041c8a7
    L_0041c89e:
        mov edx,dword ptr [ecx]
    L_0041c8a0:
        push ebx
    L_0041c8a1:
        push ebp
    L_0041c8a2:
        call dword ptr [edx+20h]
    L_0041c8a5:
        add edi,eax
    L_0041c8a7:
        test esi,esi
    L_0041c8a9:
        mov ecx,esi
    L_0041c8ab:
        jne short L_0041c895
    L_0041c8ad:
        pop esi
    L_0041c8ae:
        pop ebx
    L_0041c8af:
        mov eax,edi
    L_0041c8b1:
        pop edi
    L_0041c8b2:
        pop ebp
    L_0041c8b3:
        ret 8
    }
}
