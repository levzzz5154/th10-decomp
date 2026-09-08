#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BA00..0x0041BA2F: FUN_0041ba00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ba00_0041ba00() {
    __asm {
    L_0041ba00:
        mov edx,dword ptr [data_00477810]
    L_0041ba06:
        test edx,edx
    L_0041ba08:
        push esi
    L_0041ba09:
        mov esi,ecx
    L_0041ba0b:
        je short L_0041ba28
    L_0041ba0d:
        mov eax,dword ptr [edx+58h]
    L_0041ba10:
        mov ecx,eax
    L_0041ba12:
        shr ecx,2
    L_0041ba15:
        or ecx,eax
    L_0041ba17:
        test cl,1
    L_0041ba1a:
        jne short L_0041ba21
    L_0041ba1c:
        test ah,4
    L_0041ba1f:
        je short L_0041ba28
    L_0041ba21:
        mov eax,1
    L_0041ba26:
        pop esi
    L_0041ba27:
        ret
    L_0041ba28:
        push esi
    L_0041ba29:
        call asm_FUN_0041afd0_0041afd0
    L_0041ba2e:
        pop esi
    L_0041ba2f:
        ret
    }
}
