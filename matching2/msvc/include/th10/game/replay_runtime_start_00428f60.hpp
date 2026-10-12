#ifndef TH10_RENDER_REPLAY_RUNTIME_START_00428F60_HPP
#define TH10_RENDER_REPLAY_RUNTIME_START_00428F60_HPP
#include "th10/game/replay_manager_create_004296f0.hpp"

// The stage snapshot the bootstrap copies into the current-stage record
// and restores from it; the fields the retail body touches of the 0x1C4-
// byte allocation.
struct ReplayStageSnapshot_00428f60 {
    unsigned short reserved_00[2];       // +0x00: stage + shot words
    unsigned char reserved_04[0x0C - 0x04];
    unsigned int score;                  // +0x0C
    unsigned short lives;                // +0x10
    unsigned char reserved_12[4];
    unsigned int extends;                // +0x18
    unsigned char reserved_1c[4];
    unsigned int stage_progress;         // +0x1C
    unsigned char reserved_20[0x24 - 0x20];
    unsigned int reserved_24[2];         // +0x24, +0x28: cleared when restart
    unsigned char reserved_2c[0x1B4 - 0x2C];
    unsigned int last_spell_score;       // +0x1B4
    unsigned char reserved_1b8[8];
};

// 0x00428F60: the replay runtime's start. The receiver arrives in EBX,
// the mode in EAX and the replay path in ECX; the entry is the manager's
// own Start with the three register homes the caller (0x00429610) sets.
// Zero on success, -1 when a mode-1/2 load fails.
__declspec(noinline) int ReplayRuntime_Start_00428f60(
    int start_mode, const char* replay_path);
#endif
