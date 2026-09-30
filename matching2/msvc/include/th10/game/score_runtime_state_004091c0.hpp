#pragma once

// Score runtime state as seen by the array-release pair at 0x004091C0 and
// its scheduler callback 0x00409270.
struct ScoreRuntimeState_004091c0 {
    unsigned char reserved_0000[0x378C];
    unsigned char release_flag_378C;                 // +0x378C: release when bit 0 is set
    unsigned char reserved_378D[0x400];

    __declspec(noinline) int ReleaseFlaggedEntityArrays();
    int RunArrayReleaseCallback();
};
