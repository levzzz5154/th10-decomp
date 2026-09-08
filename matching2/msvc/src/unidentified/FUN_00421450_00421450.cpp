#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421450..0x00421472: FUN_00421450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421450_00421450() {
    __asm {
    L_00421450:
        push ebx
    L_00421451:
        mov ebx,dword ptr [data_004660bc]
    L_00421457:
        push esi
    L_00421458:
        mov esi,eax
    L_0042145a:
        push edi
    L_0042145b:
        add esi,64Ch
    L_00421461:
        mov edi,7
    L_00421466:
        push esi
    L_00421467:
        call ebx
    L_00421469:
        add esi,18h
    L_0042146c:
        dec edi
    L_0042146d:
        jne short L_00421466
    L_0042146f:
        pop edi
    L_00421470:
        pop esi
    L_00421471:
        pop ebx
    L_00421472:
        ret
    }
}
