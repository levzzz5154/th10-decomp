// Complete 0x00420A90: queue the WAV rendition of a track into a music slot.
#include <string.h>
#include "th10/game/pause_result_open/music.hpp"

#pragma code_seg(".text$00420a90_fn")
__declspec(noinline) int __stdcall Music_Load(int slot, const char* file_name) {
    char path[256];
    strcpy(path, file_name);
    char* extension = strrchr(path, '.');
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    g_music_requests.RegisterResource(path, 1, slot);
    return 1;
}
#pragma code_seg()
