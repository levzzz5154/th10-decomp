// 0x00409270: scheduler callback registered at 0x00408A11.  It hands the state
// to 0x004091C0 in EBX; both are compiled in the anm_batch_flush native-LTCG
// cluster, whose whole-program pass chooses that private receiver.
#include "th10/game/score_runtime_state_004091c0.hpp"

#pragma code_seg(".text$001releasezc")
__declspec(noinline) int ScoreRuntimeState_004091c0::RunArrayReleaseCallback() {
    return ReleaseFlaggedEntityArrays();
}
#pragma code_seg()
