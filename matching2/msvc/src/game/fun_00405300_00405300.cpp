#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00405300..0x0040533B: FUN_00405300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405300_00405300() {
    __asm {
    L_00405300:
        mov eax,ebx
    L_00405302:
        imul eax,118h
    L_00405308:
        push edi
    L_00405309:
        lea edi,[eax+esi+154h]
    L_00405310:
        mov dword ptr [esi+384h],edi
    L_00405316:
        call asm_Camera_ApplyRetail_00421480
    L_0040531b:
        mov edx,dword ptr [esi+384h]
    L_00405321:
        mov eax,dword ptr [esi+8]
    L_00405324:
        mov ecx,dword ptr [eax]
    L_00405326:
        add edx,0CCh
    L_0040532c:
        push edx
    L_0040532d:
        push eax
    L_0040532e:
        call dword ptr [ecx+0BCh]
    L_00405334:
        mov dword ptr [esi+388h],ebx
    L_0040533a:
        pop edi
    L_0040533b:
        ret
    }
}
