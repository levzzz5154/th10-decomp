#pragma once
#include <stddef.h>
#include "th10/game/game_thread_queue_native.hpp"
#include "th10/render/camera_batch.hpp"
#include "th10/game/menu_cursor.hpp"

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
// A scheduler task, as far as the screen touches it: bit 1 of the flags
// suspends the task.
struct SpriteViewerTask_0040a940 {
    int priority;
    unsigned int flags;
};
// Every game manager starts with its update and draw tasks.
struct SpriteViewerTaskPair_0040a940 {
    unsigned char reserved_000[8];
    SpriteViewerTask_0040a940* update_task;
    SpriteViewerTask_0040a940* draw_task;

    // 0x00409E20: suspend both tasks.
    __declspec(noinline) void Suspend();
    void Resume() {
        if (update_task) update_task->flags &= ~2u;
        if (draw_task) draw_task->flags &= ~2u;
    }
};
struct SpriteViewerEnemies_0040a940 : SpriteViewerTaskPair_0040a940 {
    unsigned char reserved_010[0x54 - 0x10];
    SpriteViewerParser_0040a940* parser;
    unsigned char reserved_058[8];
    int enemy_count;

    __declspec(noinline) ~SpriteViewerEnemies_0040a940();   // 0x0040D530
    // 0x0040D510: suspend both tasks.
    __declspec(noinline) void SuspendTasks();
    // 0x00409F90: remove every enemy.
    __declspec(noinline) void Clear();
};

// The viewed sprite is an animation entity; its base position is at +0x334.
struct SpriteViewerSprite_0040a940 {
    unsigned char reserved_000[0x334];
    CameraVector base_position;
    unsigned char reserved_340[0x358 - 0x340];
    void* resource;            // +0x358, owned
    unsigned char reserved_35c[0x3AC - 0x35C];

    ~SpriteViewerSprite_0040a940();   // 0x00401FF0
};

struct SchedulerTask;

// The screen's loader thread: a PlatformWorker (th10/platform/worker.hpp),
// destroyed by 0x0044C130.
struct SpriteViewerWorker_0040a940 {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;

    ~SpriteViewerWorker_0040a940();
};

// The 0x688-byte "SprtView" debug screen.
struct SpriteViewer_0040a940 {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    SpriteViewerWorker_0040a940 worker;
    unsigned char reserved_02c[4];
    int state;                 // 1 = menu, 2 = loading, 3 = viewing, 4 = enemy count
    const char** script_names;
    int script_count;
    MenuCursor menu;           // File / Ecl / Quit
    MenuCursor file_cursor;    // which script file
    MenuCursor entry_cursor;   // which entry of the loaded script
    unsigned char reserved_2c4[4];
    SpriteViewerSprite_0040a940 sprite;
    float position_x;
    float position_y;
    float position_z;
    int field_680;
    unsigned int flags;

    __declspec(noinline) ~SpriteViewer_0040a940();
    __declspec(noinline) void ClearScriptNames();
    __declspec(noinline) int Update();
    __declspec(noinline) int Draw();
};
typedef char SpriteViewerCursorOffset_0040a940[offsetof(SpriteViewer_0040a940, entry_cursor) == 0x1EC ? 1 : -1];
typedef char SpriteViewerStateOffset_0040a940[offsetof(SpriteViewer_0040a940, state) == 0x30 ? 1 : -1];
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
