#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E4D0..0x0043E4FA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043e4d0() {
    __asm {
    L_0043e4d0:
        push esi
    L_0043e4d1:
        mov esi,dword ptr [eax+5208h]
    L_0043e4d7:
        test esi,esi
    L_0043e4d9:
        je short L_0043e4f7
    L_0043e4db:
        fld dword ptr [esp+8]
    L_0043e4df:
        mov dword ptr [esi+1Ch],1
    L_0043e4e6:
        fmul dword ptr [data_00470b1c]
    L_0043e4ec:
        call asm_FUN_00463b2c_00463b2c
    L_0043e4f1:
        mov dword ptr [esi+14h],eax
    L_0043e4f4:
        mov dword ptr [esi+18h],eax
    L_0043e4f7:
        pop esi
    L_0043e4f8:
        ret 4
    }
}
