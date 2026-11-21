#ifndef TH10_REPLAY_SAVE_UPDATE_00433570_HPP
#define TH10_REPLAY_SAVE_UPDATE_00433570_HPP
#include "th10/game/replay_select_update.hpp"

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
