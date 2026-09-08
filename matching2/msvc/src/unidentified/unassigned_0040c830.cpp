#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C830..0x0040C851: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c830() {
    __asm {
    L_0040c830:
        xor eax,eax
    L_0040c832:
        push edi
    L_0040c833:
        mov dword ptr [edx],46D0F0h
    L_0040c839:
        mov dword ptr [edx+1090h],eax
    L_0040c83f:
        mov dword ptr [edx+1094h],eax
    L_0040c845:
        mov ecx,426h
    L_0040c84a:
        mov edi,edx
    L_0040c84c:
        rep stosd
    L_0040c84e:
        mov eax,edx
    L_0040c850:
        pop edi
    L_0040c851:
        ret
    }
}
