#pragma once

// Shared declaration for the paired retail callbacks at 0x004091C0 and
// 0x00409270. The LTCG layout compiles both bodies and its synthetic context
// against this one type so the private EBX receiver chosen for the array-release
// method is consistent across translation units.
struct ScoreRuntimeState_004091c0 {
    unsigned char reserved_0000[0x378C];
    unsigned char release_flag_378C;
    unsigned char reserved_378D[0x400];

    __declspec(noinline) int ReleaseFlaggedEntityArrays();
    __declspec(noinline) int RunArrayReleaseCallback();
};
