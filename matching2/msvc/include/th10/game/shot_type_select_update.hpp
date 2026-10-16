#ifndef TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#define TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#include "th10/game/difficulty_select_update.hpp"
#include "th10/game/recovery_script_executor_ascii_anchors.hpp"

// The score file seen by the shot type selection: the record of each
// character and shot type with its clear count per difficulty, and whether
// each character has cleared the game with each shot type.
struct PracticeScore {
    unsigned char reserved_00[5];
    unsigned char unlocked;     // the stage has been reached in a normal game
    unsigned char reserved_06[2];
};
struct ShotScore {
    unsigned char reserved_0000[0x4D0];
    int clears[5];
    PracticeScore practice[5][6];  // per difficulty and stage
    unsigned char reserved_05d4[0x437C - 0x5D4];
};
struct ScoreFile4 {
    ShotScore shots[2][3];
    unsigned char reserved_194e8[0x1D878 - 0x194E8];
    char last_name[9];          // +0x1D878: the name entered last time
    unsigned char reserved_1d881[7];
    unsigned char cleared[2][3];
};
typedef char ScoreFileClearedOffset[offsetof(ScoreFile4, cleared) == 0x1D888 ? 1 : -1];

// A child reference seen as the handle whose hidden flag 0x004495E0 clears.
struct AnimationHandle12 {
    RecoveryScriptId id;
    __declspec(noinline) void ClearFlag();
};

extern "C" {
extern int g_globals_shot_type;               // shot type
extern ScoreFile4* g_score;
extern unsigned int g_globals_flags;      // game flags (0x10: practice)
extern int g_globals_stage, g_globals_stage_shown;    // stage, starting stage
extern int g_main_state;               // requested application mode
extern unsigned char g_stage_routes[];   // stage table, 0x30 bytes per stage
extern unsigned char* g_stage_route_current;    // current stage record
}

// 0x00420C30.
__declspec(noinline) int __stdcall Music_FadeOut(float frames);

__declspec(noinline) int __stdcall TitleMode8(Title* room);
#endif
