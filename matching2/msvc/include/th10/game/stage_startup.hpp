#ifndef TH10_GAME_STAGE_STARTUP_00417870_HPP
#define TH10_GAME_STAGE_STARTUP_00417870_HPP
#include <stddef.h>
#include <string.h>
#include "th10/math/rng.hpp"
#include "th10/math/timer.hpp"
#include "th10/game/player.hpp"

void* __cdecl operator new(unsigned int size);

// The running game state, including its flags and initial life setting.
// The prefix is also used by the complete replay-stage compiler context.
struct StageRunState {
    int high_score;               // 0x00474C40
    int score;                    // 0x00474C44
    short word_08;                // 0x00474C48
    int gauge;                    // 0x00474C4C
    int gauge_decay;
    FrameTimer gauge_timer;       // 0x00474C54
    int character;                // 0x00474C68
    int shot_type;                // 0x00474C6C
    int lives;                    // 0x00474C70
    int difficulty;               // 0x00474C74
    int field_38;
    int stage;                    // 0x00474C7C
    int stage_shown;              // 0x00474C80
    int reserved_44[3];
    int continues;                // 0x00474C90
    int high_score_continues;     // 0x00474C94
    int rank;                     // 0x00474C98 (g_rank)
    int field_5c;                 // 0x00474C9C
    unsigned int flags;           // 0x00474CA0
    int reserved_64[2];
    int initial_lives;            // 0x00474CAC

    // 0x00418B80 (recovered as ScoreState::SetGauge).
    __declspec(noinline) void SetGauge(int amount);
};
typedef char GameStateField5c[offsetof(StageRunState, field_5c) == 0x5C ? 1 : -1];

// The 0x1C4-byte record a replay keeps for each stage.
struct ReplayStage {
    short stage;                  // +0x00
    unsigned short seed;          // +0x02: the generator seed at the stage start
    int input_count;              // +0x04: 6-byte input records after this record
    int data_size;                // +0x08: bytes from the end of this record to the next one
    int score;                    // +0x0C
    short word_10;                // +0x10
    int gauge;                    // +0x14: in units of ten
    int gauge_frame;              // +0x18
    int field_1c;
    int field_20;
    FixedPoint player_position;                    // +0x24
    FixedPoint player_position_history[33];        // +0x2C
    FixedPoint options[4][4];                      // +0x134: [PlayerOption::Point index][option]
    int continues;                // +0x1B4
    int field_1b8;
    int player_focused;           // +0x1BC
    unsigned int flag : 1;        // +0x1C0

    ReplayStage() { memset(this, 0, sizeof(*this)); }
};
typedef char ReplayStageSize[sizeof(ReplayStage) == 0x1C4 ? 1 : -1];

// The file header of a replay.
struct ReplayHeader2 {
    unsigned int magic;           // +0x00: "t10r"
    short version;                // +0x04: 5
    unsigned char reserved_06[0x16];
    int packed_size;              // +0x1C
    int size;                     // +0x20
};
typedef char ReplayHeaderSize[sizeof(ReplayHeader2) == 0x24 ? 1 : -1];

// The summary at the start of the unpacked replay; the stage records follow.
struct ReplaySummary2 {
    unsigned char reserved_00[0x4C];
    int stage_count;              // +0x4C
    unsigned char reserved_50[0x14];
};
typedef char ReplaySummarySize[sizeof(ReplaySummary2) == 0x64 ? 1 : -1];

// One stage's input list in the replay manager.
struct ReplayNode {
    unsigned char* inputs;        // +0x00
    unsigned char* cursor;        // +0x04
    unsigned char* inputs_end;    // +0x08
    unsigned char* cursor_end;    // +0x0C
    ReplayStage* stage;  // +0x10
    int count;                    // +0x14
    int reserved_18[3];
};

// A scheduler task, as far as the manager touches it.
struct ReplayTask {
    int priority;
    unsigned int flags;           // +0x04: 2 = paused for this frame
};

// The head or a node of a stage's list of input pages.
struct ReplayPoolPage;
struct ReplayPoolLink {
    ReplayPoolPage* page;
    ReplayPoolLink* next;
    ReplayPoolLink* previous;
};

// The replay manager at *0x00477838.
struct ReplayManager2 {
    unsigned char reserved_00[8];
    ReplayTask* update_task;      // +0x08
    ReplayTask* draw_task;        // +0x0C
    int mode;                     // +0x10: 0 = record, 1 = play back
    ReplayHeader2* header;         // +0x14
    ReplaySummary2* summary;       // +0x18
    ReplayStage* stage_data[8];   // +0x1C
    ReplayPoolLink pools[8];      // +0x3C: the input pages of each stage
    ReplayPoolLink* current_pool; // +0x9C
    ReplayNode nodes[8]; // +0xA0
    unsigned char* data;          // +0x1C0: the unpacked replay
    int reserved_1c4;
    int field_1c8;
    ReplayTask* extra_task;       // +0x1CC
    int stage;                    // +0x1D0: the stage being recorded or played
    char filename[0x100];         // +0x1D4

    // 0x0042A450: close the stage: save the game and player state into its
    // record, or put the recorded player state back during playback.
    __declspec(noinline) void FinishStage();

    // 0x0042AA50 (src/game/replay/linked_pool_append.cpp): allocate an
    // input page and append it to a stage's list.
    __declspec(noinline) ReplayPoolLink* AppendPage(int stage);

    // 0x0042A200: read a replay file and index its stages; -1 on failure.
    __declspec(noinline) int LoadFile(const char* filename);

    // 0x0042A6A0: start recording or playing back the current stage.
    __declspec(noinline) void BeginStage();
};
typedef char ReplayManagerNodes2[offsetof(ReplayManager2, nodes) == 0xA0 ? 1 : -1];

extern "C" StageRunState g_globals;
extern "C" RngState g_rng;
// The application object already passed to the animation cleanup functions.
struct StageApplication {
    unsigned char reserved_000[0x120];
    unsigned int configuration[13];  // +0x120: 0x00491D48
    unsigned char reserved_154[0x39C - 0x154];
    int stage_reset;                // +0x39C: 0x00491FC4
    unsigned char reserved_3a0[0x3CC - 0x3A0];
    unsigned int status;            // +0x3CC: 0x00491FF4
    unsigned char reserved_3d0[0x638 - 0x3D0];
    int worker_stop_requested;     // +0x638: worker +0x0C, 0x00492260
    int worker_running;            // +0x63C: worker +0x10, 0x00492264
};
typedef char StageApplicationReset[offsetof(StageApplication, stage_reset) == 0x39C ? 1 : -1];
typedef char StageApplicationWorkerReady[offsetof(StageApplication, worker_stop_requested) == 0x638 ? 1 : -1];
typedef char StageApplicationWorkerState[offsetof(StageApplication, worker_running) == 0x63C ? 1 : -1];
typedef char StageApplicationStatus[offsetof(StageApplication, status) == 0x3CC ? 1 : -1];
typedef char StageRunFlags[offsetof(StageRunState, flags) == 0x60 ? 1 : -1];
typedef char StageRunLives[offsetof(StageRunState, initial_lives) == 0x6C ? 1 : -1];
extern "C" StageApplication g_application;

// The published UI context is passed to the startup worker on the stack.
struct Game;
extern "C" __declspec(noinline) int __stdcall Game_Initialize(Game* context);

#endif
