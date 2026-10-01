#pragma once
#include <stddef.h>
#include "th10/game/game_thread_queue_native.hpp"
#include "th10/render/camera_batch.hpp"

struct AnimationManager_00442F50;

struct SpriteViewerEntry_0040a940 {
    const char* name;
    void* code;
};
struct SpriteViewerParser_0040a940 {
    unsigned char reserved_000[0x8C];
    SpriteViewerEntry_0040a940* entries;
};
// The enemy manager at 0x00477704, as far as the viewer reads it.
struct SpriteViewerEnemies_0040a940 {
    unsigned char reserved_000[0x54];
    SpriteViewerParser_0040a940* parser;
    unsigned char reserved_058[8];
    int enemy_count;
};

// The viewed sprite is an animation entity; its base position is at +0x334.
struct SpriteViewerSprite_0040a940 {
    unsigned char reserved_000[0x334];
    CameraVector base_position;
    unsigned char reserved_340[0x3AC - 0x340];
};

// The 0x688-byte "SprtView" debug screen.
struct SpriteViewer_0040a940 {
    unsigned char reserved_000[0x30];
    int state;                 // 1 = menu, 2 = loading, 3 = viewing, 4 = enemy count
    const char** script_names;
    int script_count;
    int menu_row;
    unsigned char reserved_040[0x114 - 0x40];
    int script_index;
    unsigned char reserved_118[0x1EC - 0x118];
    int selection;
    unsigned char reserved_1f0[0x2C8 - 0x1F0];
    SpriteViewerSprite_0040a940 sprite;
    float position_x;
    float position_y;
    unsigned char reserved_67c[8];
    unsigned int flags;

    __declspec(noinline) int Draw();
};
typedef char SpriteViewerSpriteOffset_0040a940[offsetof(SpriteViewer_0040a940, sprite) == 0x2C8 ? 1 : -1];
typedef char SpriteViewerFlagsOffset_0040a940[offsetof(SpriteViewer_0040a940, flags) == 0x684 ? 1 : -1];
typedef char SpriteViewerSize_0040a940[sizeof(SpriteViewer_0040a940) == 0x688 ? 1 : -1];

struct AnimationManager_00442F50;
extern "C" {
extern GameThread_00401530* data_004776e0;
extern SpriteViewerEnemies_0040a940* data_00477704;
extern AnimationManager_00442F50* data_00491c10;
// 0x00443080: draw one entity; the manager is on the stack and the entity
// arrives in ESI.
__declspec(noinline) int __stdcall SpriteViewer_DrawEntity_00443080(AnimationManager_00442F50* manager, SpriteViewerSprite_0040a940* entity);
}
