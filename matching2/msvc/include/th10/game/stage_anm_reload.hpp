#ifndef TH10_GAME_STAGE_ANM_RELOAD_HPP
#define TH10_GAME_STAGE_ANM_RELOAD_HPP

#include <string.h>

struct CachedResource;

// 0x00447280: the cached animation file for a slot, loading it when missing.
CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name);

struct AnimationHandle3 {
    unsigned int id;
};

// 0x00409E50: stop the animation a handle names at its first frame.
__declspec(noinline) void StopHandle2(AnimationHandle3* handle);

struct StageHeader {
    int unknown_00;
    int anm_slot;                        // +0x04
};

struct Stage3 {
    unsigned char pad_00[0x54];
    StageHeader* header;        // +0x54
    unsigned char pad_58[0x70 - 0x58];
    const char* anm_name;                // +0x70
    unsigned int flags;                  // +0x74: bit 2 asks for a reload
    unsigned char pad_78[0x80 - 0x78];
    CachedResource* anm[1];              // +0x80, by slot

    __declspec(noinline) int ReloadAnm();
};

struct StageOwner {
    unsigned char pad_00[0x18];
    Stage3* stage;               // +0x18

    __declspec(noinline) int ReloadStageAnm();
};

struct GameThread5 {
    unsigned char pad_0000[0x89A4];
    AnimationHandle3 loading_sprite;  // +0x89A4

    void StopLoadingSprite() {
        StopHandle2(&loading_sprite);
        loading_sprite.id = 0;
    }
};

extern "C" {
extern char g_recovery_script_path[];             // scratch path
extern void* g_sprt_ctrl;              // animation manager
extern GameThread5* g_ascii_manager;
extern StageOwner* g_ending;
}

extern "C" unsigned int __cdecl Stage_ReloadAnmThread2();

#endif
