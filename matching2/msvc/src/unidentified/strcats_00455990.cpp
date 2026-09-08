#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455990..0x004559B3: __strcats
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strcats_00455990() {
    __asm {
    L_00455990:
        push edi
    L_00455991:
        mov edi,dword ptr [esp+0Ch]
    L_00455995:
        test edi,edi
    L_00455997:
        jle short L_004559b2
    L_00455999:
        push esi
    L_0045599a:
        lea esi,[esp+10h]
    L_0045599e:
        add esi,4
    L_004559a1:
        push dword ptr [esi]
    L_004559a3:
        push dword ptr [esp+10h]
    L_004559a7:
        call asm_FUN_0045bd90_0045bd90
    L_004559ac:
        dec edi
    L_004559ad:
        pop ecx
    L_004559ae:
        pop ecx
    L_004559af:
        jne short L_0045599e
    L_004559b1:
        pop esi
    L_004559b2:
        pop edi
    L_004559b3:
        ret
    }
}
