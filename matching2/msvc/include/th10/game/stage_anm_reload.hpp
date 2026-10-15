#ifndef TH10_GAME_STAGE_ANM_RELOAD_HPP
#define TH10_GAME_STAGE_ANM_RELOAD_HPP

#include <string.h>

struct CachedResource;

// 0x00447280: the cached animation file for a slot, loading it when missing.
CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name);

struct AnimationHandle_0040c3c0 {
    unsigned int id;
};

// 0x00409E50: stop the animation a handle names at its first frame.
__declspec(noinline) void StopHandle_00409e50(AnimationHandle_0040c3c0* handle);

struct StageHeader_0040c3c0 {
    int unknown_00;
    int anm_slot;                        // +0x04
};

struct Stage_0040c3c0 {
    unsigned char pad_00[0x54];
    StageHeader_0040c3c0* header;        // +0x54
    unsigned char pad_58[0x70 - 0x58];
    const char* anm_name;                // +0x70
    unsigned int flags;                  // +0x74: bit 2 asks for a reload
    unsigned char pad_78[0x80 - 0x78];
    CachedResource* anm[1];              // +0x80, by slot

    __declspec(noinline) int ReloadAnm();
};

struct StageOwner_0040c3c0 {
    unsigned char pad_00[0x18];
    Stage_0040c3c0* stage;               // +0x18

    __declspec(noinline) int ReloadStageAnm();
};

struct GameThread_0040c3c0 {
    unsigned char pad_0000[0x89A4];
    AnimationHandle_0040c3c0 loading_sprite;  // +0x89A4

    void StopLoadingSprite() {
        StopHandle_00409e50(&loading_sprite);
        loading_sprite.id = 0;
    }
};

extern "C" {
extern char data_00497c38[];             // scratch path
extern void* g_sprt_ctrl;              // animation manager
extern GameThread_0040c3c0* g_ascii_manager;
extern StageOwner_0040c3c0* g_ending;
}

extern "C" unsigned int __cdecl Stage_ReloadAnmThread_0040c3a0();

#endif
