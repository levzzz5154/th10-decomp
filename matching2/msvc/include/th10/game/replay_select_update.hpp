#ifndef TH10_REPLAY_SELECT_UPDATE_004315C0_HPP
#define TH10_REPLAY_SELECT_UPDATE_004315C0_HPP
#include <string.h>
#include "th10/game/practice_stage_select_update.hpp"

// The replay file header as far as the screen reads it.
struct ReplayFileHeader2 {
    unsigned char reserved_00[0xC];
    int date;           // +0x0C, time() of the save
    unsigned char reserved_10[0x50 - 0x10];
    int character;      // +0x50
    int shot_type;      // +0x54
    int difficulty;     // +0x58
    int stage;          // +0x5C, 8 for a whole game
};
// One stage of an opened replay.
struct ReplayFileStage {
    unsigned char reserved_00[0x10];
    int recorded;       // +0x10, nonzero when the replay holds the stage
    unsigned char reserved_14[0x10];
};
// An opened replay (the 0x2D4-byte replay manager of
// include/th10/game/replay_manager_create.hpp) as far as the screen
// reads it.
struct ReplayFile {
    unsigned char reserved_000[0x18];
    ReplayFileHeader2* header;      // +0x18
    unsigned char reserved_01c[0xC4 - 0x1C];
    ReplayFileStage stages[7];     // +0xC4
    unsigned char reserved_1c0[0x1D4 - 0x1C0];
    char path[0x100];                       // +0x1D4
};
typedef char ReplayFilePath[offsetof(ReplayFile, path) == 0x1D4 ? 1 : -1];

// The title screen object past the music-room view: the replays offered by
// the replay selection (25 numbered ones, then up to 25 user-named ones).
struct TitleReplayView {
    unsigned char reserved_0000[0x59D8];
    int reserved_59d8;
    int selected_replay;                // +0x59DC
    int selected_stage;                 // +0x59E0
    ReplayFile* replays[50];   // +0x59E4
};
typedef char ReplaySelectRoomSize[sizeof(TitleReplayView) == 0x5AAC ? 1 : -1];

// WIN32_FIND_DATAA.
struct ReplayFindData {
    unsigned int attributes;
    unsigned int times[6];
    unsigned int size_high, size_low, reserved0, reserved1;
    char name[260];
    char alternate_name[14];
};

extern "C" {
extern int g_title_replay_selection;               // replay selected last time
extern int g_main_mode_request;               // main task mode request
extern char g_replay_path[];            // path of the replay to play
int __cdecl sprintf(char* buffer, const char* format, ...);
int __cdecl _mkdir(const char* path);
int __cdecl _chdir(const char* path);
void __cdecl free(void* block);
__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, ReplayFindData* data);
__declspec(dllimport) int __stdcall FindNextFileA(void* search, ReplayFindData* data);
__declspec(dllimport) int __stdcall FindClose(void* search);
}
// 0x004296F0: open a replay file; null when it cannot be read.
__declspec(noinline) ReplayFile* __stdcall ReplayFile_Open(const char* path);
// 0x004294A0: the destructor of an opened replay.
__declspec(noinline) void __stdcall ReplayFile_Destroy(ReplayFile* replay);

__declspec(noinline) int __stdcall TitleMode12(Title* room);
#endif
