#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x0041C7D0..0x0041C7FB: ?ScoreRecords_MarkEligible@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreRecords_MarkEligible_0041c7d0() {
    __asm {
    L_0041c7d0:
        mov eax,dword ptr [eax+18h]
    L_0041c7d3:
        test eax,eax
    L_0041c7d5:
        je short L_0041c7f9
    L_0041c7d7:
        push ebx
    L_0041c7d8:
        mov edx,1
    L_0041c7dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041c7e0:
        cmp dword ptr [eax+0Ch],edx
    L_0041c7e3:
        mov ecx,dword ptr [eax+8]
    L_0041c7e6:
        je short L_0041c7f2
    L_0041c7e8:
        mov bl,byte ptr [eax+50h]
    L_0041c7eb:
        test bl,bl
    L_0041c7ed:
        jne short L_0041c7f2
    L_0041c7ef:
        mov byte ptr [eax+50h],dl
    L_0041c7f2:
        test ecx,ecx
    L_0041c7f4:
        mov eax,ecx
    L_0041c7f6:
        jne short L_0041c7e0
    L_0041c7f8:
        pop ebx
    L_0041c7f9:
        xor eax,eax
    L_0041c7fb:
        ret
    }
}
