#ifndef TH10_GAME_REPLAY_STAGE_FINISH_0042A450_HPP
#define TH10_GAME_REPLAY_STAGE_FINISH_0042A450_HPP
#include "th10/game/replay_stage_begin.hpp"

// 0x0042AB20 (src/game/replay/linked_pool_release.cpp): free the input pages of a stage.
extern "C" void __stdcall ReplayFinishClearPools(ReplayManager2* manager, int stage);
// 0x00426F70: recompute the options from the power level.
extern "C" void __stdcall PlayerRefresh2(Player* player);
// 0x00424D90 (src/game/player/pause_menu_reset.cpp): reset the player's pause timers.
struct PauseState2;
extern "C" void __stdcall ReplayPauseReset(PauseState2* owner);

#endif
