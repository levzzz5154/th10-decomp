#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435280..0x004352B2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00435280() {
    __asm {
    L_00435280:
        mov eax,dword ptr [edx]
    L_00435282:
        push esi
    L_00435283:
        lea esi,[eax+1]
    L_00435286:
        mov cl,byte ptr [eax]
    L_00435288:
        inc eax
    L_00435289:
        test cl,cl
    L_0043528b:
        jne short L_00435286
    L_0043528d:
        sub eax,esi
    L_0043528f:
        lea ecx,[eax+1]
    L_00435292:
        mov eax,ecx
    L_00435294:
        and eax,80000003h
    L_00435299:
        jns short L_004352a0
    L_0043529b:
        dec eax
    L_0043529c:
        or eax,0FFFFFFFCh
    L_0043529f:
        inc eax
    L_004352a0:
        je short L_004352ab
    L_004352a2:
        mov esi,4
    L_004352a7:
        sub esi,eax
    L_004352a9:
        add ecx,esi
    L_004352ab:
        mov eax,dword ptr [edx]
    L_004352ad:
        add eax,ecx
    L_004352af:
        mov dword ptr [edx],eax
    L_004352b1:
        pop esi
    L_004352b2:
        ret
    }
}
