#ifndef TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#define TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#include "th10/game/difficulty_select_update_00430320.hpp"
#include "th10/game/recovery_script_executor_ascii_anchors.hpp"

// The score file seen by the shot type selection: the record of each
// character and shot type with its clear count per difficulty, and whether
// each character has cleared the game with each shot type.
struct PracticeScore_00430a60 {
    unsigned char reserved_00[5];
    unsigned char unlocked;     // the stage has been reached in a normal game
    unsigned char reserved_06[2];
};
struct ShotScore_00430a60 {
    unsigned char reserved_0000[0x4D0];
    int clears[5];
    PracticeScore_00430a60 practice[5][6];  // per difficulty and stage
    unsigned char reserved_05d4[0x437C - 0x5D4];
};
struct ScoreFile_00430a60 {
    ShotScore_00430a60 shots[2][3];
    unsigned char reserved_194e8[0x1D888 - 0x194E8];
    unsigned char cleared[2][3];
};
typedef char ScoreFileClearedOffset_00430a60[offsetof(ScoreFile_00430a60, cleared) == 0x1D888 ? 1 : -1];

// A child reference seen as the handle whose hidden flag 0x004495E0 clears.
struct AnimationHandle_004495e0 {
    RecoveryScriptId_0040bd80 id;
    __declspec(noinline) void ClearFlag();
};

extern "C" {
extern int data_00474c6c;               // shot type
extern ScoreFile_00430a60* data_0047783c;
extern unsigned int data_00474ca0;      // game flags (0x10: practice)
extern int data_00474c7c, data_00474c80;    // stage, starting stage
extern int data_00491fb8;               // requested application mode
extern unsigned char data_00474788[];   // stage table, 0x30 bytes per stage
extern unsigned char* data_00477848;    // current stage record
}

// 0x00420C30.
__declspec(noinline) int __stdcall Music_FadeOut(float frames);

__declspec(noinline) int __stdcall TitleMode8_00430a60(RecoveryMusicRoom_00433ef0* room);
#endif
