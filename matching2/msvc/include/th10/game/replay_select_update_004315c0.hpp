#ifndef TH10_REPLAY_SELECT_UPDATE_004315C0_HPP
#define TH10_REPLAY_SELECT_UPDATE_004315C0_HPP
#include <string.h>
#include "th10/game/practice_stage_select_update_00430ff0.hpp"

// The replay file header as far as the screen reads it.
struct ReplayFileHeader_004315c0 {
    unsigned char reserved_00[0x50];
    int character;      // +0x50
    int shot_type;      // +0x54
    int difficulty;     // +0x58
};
// One stage of an opened replay.
struct ReplayFileStage_004315c0 {
    unsigned char reserved_00[0x10];
    int recorded;       // +0x10, nonzero when the replay holds the stage
    unsigned char reserved_14[0x10];
};
// An opened replay (the 0x2D4-byte replay manager of
// include/th10/game/replay_manager_create_004296f0.hpp) as far as the screen
// reads it.
struct ReplayFile_004315c0 {
    unsigned char reserved_000[0x18];
    ReplayFileHeader_004315c0* header;      // +0x18
    unsigned char reserved_01c[0xC4 - 0x1C];
    ReplayFileStage_004315c0 stages[7];     // +0xC4
    unsigned char reserved_1c0[0x1D4 - 0x1C0];
    char path[0x100];                       // +0x1D4
};
typedef char ReplayFilePath_004315c0[offsetof(ReplayFile_004315c0, path) == 0x1D4 ? 1 : -1];

// The title screen object past the music-room view: the replays offered by
// the replay selection (25 numbered ones, then up to 25 user-named ones).
struct ReplaySelectRoom_004315c0 {
    unsigned char reserved_0000[0x59D8];
    int reserved_59d8;
    int selected_replay;                // +0x59DC
    int selected_stage;                 // +0x59E0
    ReplayFile_004315c0* replays[50];   // +0x59E4
};
typedef char ReplaySelectRoomSize_004315c0[sizeof(ReplaySelectRoom_004315c0) == 0x5AAC ? 1 : -1];

// WIN32_FIND_DATAA.
struct ReplayFindData_004315c0 {
    unsigned int attributes;
    unsigned int times[6];
    unsigned int size_high, size_low, reserved0, reserved1;
    char name[260];
    char alternate_name[14];
};

extern "C" {
extern int data_00491c04;               // replay selected last time
extern int data_00491c00;               // main task mode request
extern char data_00477710[];            // path of the replay to play
int __cdecl sprintf(char* buffer, const char* format, ...);
int __cdecl _mkdir(const char* path);
int __cdecl _chdir(const char* path);
void __cdecl free(void* block);
__declspec(dllimport) void* __stdcall FindFirstFileA(const char* pattern, ReplayFindData_004315c0* data);
__declspec(dllimport) int __stdcall FindNextFileA(void* search, ReplayFindData_004315c0* data);
__declspec(dllimport) int __stdcall FindClose(void* search);
}
// 0x004296F0: open a replay file; null when it cannot be read.
__declspec(noinline) ReplayFile_004315c0* __stdcall ReplayFile_Open_004296f0(const char* path);
// 0x004294A0: the destructor of an opened replay.
__declspec(noinline) void __stdcall ReplayFile_Destroy_004294a0(ReplayFile_004315c0* replay);

__declspec(noinline) int __stdcall TitleMode12_004315c0(RecoveryMusicRoom_00433ef0* room);
#endif
