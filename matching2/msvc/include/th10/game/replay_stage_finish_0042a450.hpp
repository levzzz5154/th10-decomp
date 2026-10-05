#ifndef TH10_GAME_REPLAY_STAGE_FINISH_0042A450_HPP
#define TH10_GAME_REPLAY_STAGE_FINISH_0042A450_HPP
#include "th10/game/replay_stage_begin_0042a6a0.hpp"

// One of the player's four options: four two-word values and a flag.
struct PlayerOption_0042a450 {
    ReplayOptionPair_0042a6a0 values[4];  // +0x00
    unsigned char reserved_20[0x38];
    int flag;                             // +0x58
    unsigned char reserved_5c[0x3C];
};
typedef char PlayerOptionSize_0042a450[sizeof(PlayerOption_0042a450) == 0x98 ? 1 : -1];

// The player object at *0x00477834, as far as a replay saves it.
struct Player_0042a450 {
    unsigned char reserved_0000[0x3CC];
    ReplayGaugeCounters_0042a6a0 boss_gauge;   // +0x3CC
    unsigned char reserved_03d4[0x32D4 - 0x3D4];
    PlayerOption_0042a450 options[4];          // +0x32D4
    unsigned char reserved_3534[0x436C - 0x3534];
    unsigned char state[0x108];                // +0x436C
    int field_4474;                            // +0x4474

    // 0x00428E10 (recovered in src/game/fun_00428e10_00428e10.cpp): take the
    // boss gauge counters and republish the gauge.
    __declspec(noinline) int SetBossGauge(const ReplayGaugeCounters_0042a6a0* source);
};
typedef char PlayerField4474_0042a450[offsetof(Player_0042a450, field_4474) == 0x4474 ? 1 : -1];

extern "C" Player_0042a450* data_00477834;

// 0x0042AB20 (src/game/linked_pool_release.cpp): free the input pages of a stage.
extern "C" void __stdcall ReplayFinishClearPools_0042ab20(ReplayManager_0042a6a0* manager, int stage);
// 0x00426F70 (still assembly): rebuild the player's derived state.
extern "C" void __stdcall PlayerRefresh_00426f70(Player_0042a450* player);
// 0x00424D90 (src/game/pause_menu_reset.cpp): reset the player's pause timers.
struct PauseState_00424d90;
extern "C" void __stdcall ReplayPauseReset_00424d90(PauseState_00424d90* owner);

#endif
