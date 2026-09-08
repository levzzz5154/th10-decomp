#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454BBC..0x00454BF6: __SEH_prolog
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SEH_prolog_00454bbc() {
    __asm {
    L_00454bbc:
        push 454C10h
    L_00454bc1:
        mov eax,dword ptr fs:[0]
    L_00454bc7:
        push eax
    L_00454bc8:
        mov eax,dword ptr [esp+10h]
    L_00454bcc:
        mov dword ptr [esp+10h],ebp
    L_00454bd0:
        lea ebp,[esp+10h]
    L_00454bd4:
        sub esp,eax
    L_00454bd6:
        push ebx
    L_00454bd7:
        push esi
    L_00454bd8:
        push edi
    L_00454bd9:
        mov eax,dword ptr [ebp-8]
    L_00454bdc:
        mov dword ptr [ebp-18h],esp
    L_00454bdf:
        push eax
    L_00454be0:
        mov eax,dword ptr [ebp-4]
    L_00454be3:
        mov dword ptr [ebp-4],0FFFFFFFFh
    L_00454bea:
        mov dword ptr [ebp-8],eax
    L_00454bed:
        lea eax,[ebp-10h]
    L_00454bf0:
        mov dword ptr fs:[0],eax
    L_00454bf6:
        ret
    }
}
