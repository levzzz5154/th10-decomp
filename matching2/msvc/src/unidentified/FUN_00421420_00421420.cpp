#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421420..0x00421442: FUN_00421420
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421420_00421420() {
    __asm {
    L_00421420:
        push ebx
    L_00421421:
        mov ebx,dword ptr [data_004660b8]
    L_00421427:
        push esi
    L_00421428:
        mov esi,eax
    L_0042142a:
        push edi
    L_0042142b:
        add esi,64Ch
    L_00421431:
        mov edi,7
    L_00421436:
        push esi
    L_00421437:
        call ebx
    L_00421439:
        add esi,18h
    L_0042143c:
        dec edi
    L_0042143d:
        jne short L_00421436
    L_0042143f:
        pop edi
    L_00421440:
        pop esi
    L_00421441:
        pop ebx
    L_00421442:
        ret
    }
}
