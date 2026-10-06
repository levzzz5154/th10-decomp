#ifndef TH10_GAME_STAGE_STARTUP_00417870_HPP
#define TH10_GAME_STAGE_STARTUP_00417870_HPP
#include <stddef.h>
#include <string.h>
#include "th10/math/rng.hpp"
#include "th10/math/timer.hpp"

void* __cdecl operator new(unsigned int size);

// The running game state, including its flags and initial life setting.
// The prefix is also used by the complete replay-stage compiler context.
struct StageRunState_00417870 {
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
    int field_58;                 // 0x00474C98
    int field_5c;                 // 0x00474C9C
    unsigned int flags;           // 0x00474CA0
    int reserved_64[2];
    int initial_lives;            // 0x00474CAC

    // 0x00418B80 (recovered as ScoreState::SetGauge).
    __declspec(noinline) void SetGauge(int amount);
};
typedef char GameStateField5c_0042a6a0[offsetof(StageRunState_00417870, field_5c) == 0x5C ? 1 : -1];

// The boss gauge's two counters.
struct ReplayGaugeCounters_0042a6a0 {
    int value;
    int maximum;
};

// One two-word value of a player option.
struct ReplayOptionPair_0042a6a0 {
    int x;
    int y;

    // Copied member by member; the compiler's own block copy picks other
    // loop pointers.
    ReplayOptionPair_0042a6a0& operator=(const ReplayOptionPair_0042a6a0& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
};

// The 0x1C4-byte record a replay keeps for each stage.
struct ReplayStage_0042a6a0 {
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
    ReplayGaugeCounters_0042a6a0 boss_gauge;       // +0x24
    unsigned char player_state[0x108];             // +0x2C: the block at player +0x436C
    ReplayOptionPair_0042a6a0 options[4][4];       // +0x134: [value kind][option]
    int continues;                // +0x1B4
    int field_1b8;
    int player_field_4474;        // +0x1BC
    unsigned int flag : 1;        // +0x1C0

    ReplayStage_0042a6a0() { memset(this, 0, sizeof(*this)); }
};
typedef char ReplayStageSize_0042a6a0[sizeof(ReplayStage_0042a6a0) == 0x1C4 ? 1 : -1];

// The file header of a replay.
struct ReplayHeader_0042a6a0 {
    unsigned int magic;           // +0x00: "t10r"
    short version;                // +0x04: 5
    unsigned char reserved_06[0x16];
    int packed_size;              // +0x1C
    int size;                     // +0x20
};
typedef char ReplayHeaderSize_0042a6a0[sizeof(ReplayHeader_0042a6a0) == 0x24 ? 1 : -1];

// The summary at the start of the unpacked replay; the stage records follow.
struct ReplaySummary_0042a6a0 {
    unsigned char reserved_00[0x4C];
    int stage_count;              // +0x4C
    unsigned char reserved_50[0x14];
};
typedef char ReplaySummarySize_0042a6a0[sizeof(ReplaySummary_0042a6a0) == 0x64 ? 1 : -1];

// One stage's input list in the replay manager.
struct ReplayNode_0042a6a0 {
    unsigned char* inputs;        // +0x00
    unsigned char* cursor;        // +0x04
    unsigned char* inputs_end;    // +0x08
    unsigned char* cursor_end;    // +0x0C
    ReplayStage_0042a6a0* stage;  // +0x10
    int count;                    // +0x14
    int reserved_18[3];
};

// A scheduler task, as far as the manager touches it.
struct ReplayTask_0042a6a0 {
    int priority;
    unsigned int flags;           // +0x04: 2 = paused for this frame
};

// The head or a node of a stage's list of input pages.
struct ReplayPoolPage_0042a6a0;
struct ReplayPoolLink_0042a6a0 {
    ReplayPoolPage_0042a6a0* page;
    ReplayPoolLink_0042a6a0* next;
    ReplayPoolLink_0042a6a0* previous;
};

// The replay manager at *0x00477838.
struct ReplayManager_0042a6a0 {
    unsigned char reserved_00[8];
    ReplayTask_0042a6a0* update_task;      // +0x08
    ReplayTask_0042a6a0* draw_task;        // +0x0C
    int mode;                     // +0x10: 0 = record, 1 = play back
    ReplayHeader_0042a6a0* header;         // +0x14
    ReplaySummary_0042a6a0* summary;       // +0x18
    ReplayStage_0042a6a0* stage_data[8];   // +0x1C
    ReplayPoolLink_0042a6a0 pools[8];      // +0x3C: the input pages of each stage
    ReplayPoolLink_0042a6a0* current_pool; // +0x9C
    ReplayNode_0042a6a0 nodes[8]; // +0xA0
    unsigned char* data;          // +0x1C0: the unpacked replay
    int reserved_1c4;
    int field_1c8;
    ReplayTask_0042a6a0* extra_task;       // +0x1CC
    int stage;                    // +0x1D0: the stage being recorded or played
    char filename[0x100];         // +0x1D4

    // 0x0042A450: close the stage: save the game and player state into its
    // record, or put the recorded player state back during playback.
    __declspec(noinline) void FinishStage();

    // 0x0042AA50 (src/game/linked_pool_append_0042aa50.cpp): allocate an
    // input page and append it to a stage's list.
    __declspec(noinline) ReplayPoolLink_0042a6a0* AppendPage(int stage);

    // 0x0042A200: read a replay file and index its stages; -1 on failure.
    __declspec(noinline) int LoadFile(const char* filename);

    // 0x0042A6A0: start recording or playing back the current stage.
    __declspec(noinline) void BeginStage();
};
typedef char ReplayManagerNodes_0042a6a0[offsetof(ReplayManager_0042a6a0, nodes) == 0xA0 ? 1 : -1];

extern "C" StageRunState_00417870 data_00474c40;
extern "C" RngState data_004918b0;
// The application object already passed to the animation cleanup functions.
struct StageApplication_00417870 {
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
typedef char StageApplicationReset[offsetof(StageApplication_00417870, stage_reset) == 0x39C ? 1 : -1];
typedef char StageApplicationWorkerReady[offsetof(StageApplication_00417870, worker_stop_requested) == 0x638 ? 1 : -1];
typedef char StageApplicationWorkerState[offsetof(StageApplication_00417870, worker_running) == 0x63C ? 1 : -1];
typedef char StageApplicationStatus[offsetof(StageApplication_00417870, status) == 0x3CC ? 1 : -1];
typedef char StageRunFlags[offsetof(StageRunState_00417870, flags) == 0x60 ? 1 : -1];
typedef char StageRunLives[offsetof(StageRunState_00417870, initial_lives) == 0x6C ? 1 : -1];
extern "C" StageApplication_00417870 data_00491c28;

// The published UI context is passed to the startup worker on the stack.
struct StageStartup_00417870;
extern "C" __declspec(noinline) int __stdcall StageStartup(StageStartup_00417870* context);

#endif
