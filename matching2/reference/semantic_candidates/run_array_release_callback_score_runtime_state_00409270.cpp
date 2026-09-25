#include "th10/game/score_runtime_state_release.hpp"

// 0x00409270..0x00409279: scheduler callback for the score runtime state.
// With ReleaseFlaggedEntityArrays visible to /LTCG, the pass gives this
// callback the public ECX receiver and forwards the state in EBX to the paired
// array-release body.
#pragma code_seg(".text$001callback")
int ScoreRuntimeState_004091c0::RunArrayReleaseCallback() {
    return ReleaseFlaggedEntityArrays();
}
#pragma code_seg()
