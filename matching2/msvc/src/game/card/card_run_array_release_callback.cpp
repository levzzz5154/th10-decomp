// 0x00409270: scheduler callback registered at 0x00408A11.  It hands the state
// to 0x004091C0 in EBX; both are compiled in the anm_batch_flush native-LTCG
// cluster, whose whole-program pass chooses that private receiver.
#include "th10/game/card_runtime.hpp"

#pragma code_seg(".text$001releasezc")
__declspec(noinline) int CardRuntime::RunArrayReleaseCallback() {
    return ReleaseFlaggedEntityArrays();
}
#pragma code_seg()
