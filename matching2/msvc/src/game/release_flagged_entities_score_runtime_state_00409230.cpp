#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x00409230..0x00409261: ?ReleaseFlaggedEntities@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ReleaseFlaggedEntities_ScoreRuntimeState_00409230() {
    __asm {
    L_00409230:
        push esi
    L_00409231:
        mov esi,ecx
    L_00409233:
        test byte ptr [esi+378Ch],1
    L_0040923a:
        je short L_0040925b
    L_0040923c:
        mov ecx,dword ptr [data_00491c10]
    L_00409242:
        lea eax,[esi+10h]
    L_00409245:
        call asm_FUN_004451c0_004451c0
    L_0040924a:
        mov ecx,dword ptr [data_00491c10]
    L_00409250:
        lea eax,[esi+3BCh]
    L_00409256:
        call asm_FUN_004451c0_004451c0
    L_0040925b:
        mov eax,1
    L_00409260:
        pop esi
    L_00409261:
        ret
    }
}
