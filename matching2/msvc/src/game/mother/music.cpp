#include "th10/source_views/music_requests_0b68f8_0.hpp"
__declspec(noinline) int __stdcall Music_Load(int slot, const char* file_name) {
    char path[256];
    strcpy(path, file_name);
    char* extension = strrchr(path, '.');
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    g_music_requests.RegisterResource(path, kMusicCommandLoad, slot);
    return 1;
}


#include "../../../include/th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
__declspec(noinline) int __stdcall Music_Play(int track, int heard_index) {
    if (g_config_flags & kConfigStreamedMusic)
        g_music_requests.RegisterResource("dummy", kMusicCommandStreamedReset, 0);
    g_music_requests.RegisterResource("dummy", kMusicCommandPlay, track);
    g_music_progress->track_heard[heard_index] = 1;
    return 0;
}


#include "../../../include/th10/source_views/music_requests_0b68f8_2.hpp"
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_2.hpp"
__declspec(noinline) int __stdcall Music_PlayFile(int heard_index, const char* file_name) {
    char path[256];
    strcpy(path, file_name);
    char* extension = strrchr(path, '.');
    extension[1] = 'w';
    extension[2] = 'a';
    extension[3] = 'v';
    g_music_progress->track_heard[heard_index] = 1;
    g_music_requests.RegisterResource(path, kMusicCommandPlay, -1);
    return 0;
}


#include "../../../include/th10/source_views/music_requests_0b68f8_3.hpp"
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_2.hpp"
#include "th10/source_views/music_requests_0b68f8_3.hpp"
__declspec(noinline) int __stdcall Music_Stop() {
    if (g_config_flags & kConfigStreamedMusic)
        g_music_requests.RegisterResource("dummy", kMusicCommandStreamedReset, 0);
    else
        g_music_requests.RegisterResource("dummy", kMusicCommandStop, 0);
    return 0;
}


#include "../../../include/th10/source_views/music_requests_0b68f8_4.hpp"
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_2.hpp"
#include "th10/source_views/music_requests_0b68f8_3.hpp"
#include "th10/source_views/music_requests_0b68f8_4.hpp"
__declspec(noinline) int __stdcall Music_FadeOut(float frames) {
    // Keep the branch-specific integer conversions: the native compiler
    // merges their x87 conversion tail without preloading frames too early.
    int duration;
    if (g_game_speed == 0.0f) duration = (int)frames;
    else duration = (int)(g_game_speed > 1.0f ? frames : frames / g_game_speed);
    g_music_requests.RegisterResource("", kMusicCommandFadeOut, duration);
    return 0;
}

