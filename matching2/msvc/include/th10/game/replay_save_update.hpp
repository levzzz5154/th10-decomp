#ifndef TH10_REPLAY_SAVE_UPDATE_00433570_HPP
#define TH10_REPLAY_SAVE_UPDATE_00433570_HPP
#include "th10/game/replay_select_update.hpp"

// The title screen object past the music-room view as the replay save screen
// and the high score name entry use it: the name being typed, the cursor on
// the character grid and the 25 numbered replays.
struct TitleReplaySaveView {
    unsigned char reserved_0000[0x58DC];
    char name[12];                      // +0x58DC
    int name_length;                    // +0x58E8
    int name_confirmed;                 // +0x58EC, high score entry: nothing to type
    int reserved_58f0;
    MenuCursor grid;                    // +0x58F4
    unsigned char reserved_59cc[0x59DC - 0x59CC];
    int selected_replay;                // +0x59DC
    int selected_stage;                 // +0x59E0
    ReplayFile* replays[50];   // +0x59E4
};
typedef char ReplaySaveRoomGrid[offsetof(TitleReplaySaveView, grid) == 0x58F4 ? 1 : -1];
typedef char ReplaySaveRoomSize[sizeof(TitleReplaySaveView) == 0x5AAC ? 1 : -1];

extern "C" {
extern ReplayFile* g_replay;  // the replay just recorded
extern const char* g_name_entry_grid;           // the name entry character grid
int __cdecl time2(int* out);
}
// 0x004297B0: destroy and free an opened replay, if there is one.
__declspec(noinline) void __stdcall ReplayFile_Delete(ReplayFile* replay);
// 0x00429B60: write the recorded replay to `path` under `name`.
__declspec(noinline) void __fastcall ReplayFile_Save(
    ReplayFile* replay, const char* path, const char* name);
// 0x00420A90, 0x00420B10.
__declspec(noinline) int __stdcall Music_Load2(int slot, const char* file_name);
__declspec(noinline) int __stdcall Music_Play2(int track, int heard_index);

__declspec(noinline) int __stdcall TitleMode16(Title* room);
#endif
