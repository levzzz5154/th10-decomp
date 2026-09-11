#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x00409270..0x00409279: ?RunArrayReleaseCallback@ScoreRuntimeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RunArrayReleaseCallback_ScoreRuntimeState_00409270() {
    __asm {
    L_00409270:
        push ebx
    L_00409271:
        mov ebx,ecx
    L_00409273:
        call asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0
    L_00409278:
        pop ebx
    L_00409279:
        ret
    }
}
