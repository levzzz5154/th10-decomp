// 0x0041F990: body of the loading screen's worker thread. Loads the logo and text
// animations, initialises text drawing and the BGM format table, prepares the
// sound effects and the music file, then wakes the title's tick task. A
// failure before the text animation is in place requests application state 3.
//
// The routine is installed as a thread start address and never reads the
// owner it nominally receives in ECX: every field goes through the global
// owner pointer. Its one use of the receiver is the LoadStartupResources call,
// whose body ignores `this`. The whole-program pass drops that argument at the
// call, but only after the receiver has been given a stack home, which is
// retail's unread `mov [esp+4],ecx`.
#include <string.h>
#include "th10/app/supervisor.hpp"
#include "th10/game/loading_view.hpp"
#include "../../../build_support/layout/ltcg/sound_interfaces_dependencies/sound_wave_types.hpp"
#pragma intrinsic(strcpy)

extern "C" {
extern LoadingView* g_loading;
extern void* g_sprt_ctrl;              // animation manager
extern void* data_00491fec;              // text.anm
extern char* data_00494514;              // BGM format table
extern unsigned char data_00491d78;      // sound option flags
extern char data_0046dc28[];             // "error : 文字の初期化に失敗しました"
extern char data_0046dbec[];             // "error : BGM の初期化に失敗しました"
extern TextLog_0044b810 g_log;
extern WaveSoundManager g_wave_sound_manager;

void* __fastcall Recovery_LoadCachedResource_00447280(int index, void* cache, const char* name);
void* __stdcall AsciiManager_Create();
char* __stdcall Archive_LoadFile(const char* name, int* out_size, int from_disk);
}
int __stdcall asm_File_ProbeExists_0044b4d0(const char* name);
void __stdcall ScoreManager_Create_0042af20();

// Everything the title screen itself needs; -1 when any of it is missing.
static __forceinline int LoadTitleScreenAssets(LoadingView* title) {
    title->logo_animation = Recovery_LoadCachedResource_00447280(1, g_sprt_ctrl, "sig.anm");
    if (!title->logo_animation)
        return -1;
    title->secondary_task->reserved_flags |= 1u;
    title->logo_loaded = 1;
    if (!AsciiManager_Create()) {
        g_log.Append(data_0046dc28);
        return -1;
    }
    title->game_thread_created = 1;
    data_00491fec = Recovery_LoadCachedResource_00447280(0, g_sprt_ctrl, "text.anm");
    if (!data_00491fec)
        return -1;
    return 0;
}

#pragma code_seg(".text$00title")
__declspec(noinline) int __fastcall Loading_LoadAssets_0041f990(LoadingView* owner) {
    LoadingView* title = g_loading;
    if (LoadTitleScreenAssets(title) != 0) {
        g_supervisor.next_state = 3;
        title->primary_task->reserved_flags |= 1u;
        return 0;
    }
    data_00494514 = Archive_LoadFile("../../bgm/thbgm.fmt", 0, 0);
    if (!data_00494514)
        g_log.Append(data_0046dbec);
    g_wave_sound_manager.InitializeEffects();
    if (asm_File_ProbeExists_0044b4d0("thbgm.dat")) {
        if (!(data_00491d78 & 0x10))
            g_wave_sound_manager.LaunchMusic("thbgm.dat");
        else
            strcpy(g_wave_sound_manager.music_file_name, "thbgm.dat");
    }
    owner->LoadStartupResources();
    title->primary_task->reserved_flags |= 1u;
    ScoreManager_Create_0042af20();
    return 0;
}
#pragma code_seg()
