#pragma once
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"

// The real initializer used by this graph has one genuine Entity* input.
// The legacy two-input declaration in entity.hpp is never called here.
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);

struct AnimationScriptId { int value; };
struct AnimationLookupContext;
__declspec(noinline) void* __fastcall AnimationManager_Find_004491c0(
    AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void* __fastcall AnimationManager_SetFlag_004492a0(
    AnimationLookupContext* context, AnimationScriptId id);
extern "C" AnimationLookupContext* g_sprt_ctrl;

struct Ref4 {
    int value;
    Ref4(int value) : value(value) {}
    void MarkAndClear() {
        AnimationScriptId& id = *reinterpret_cast<AnimationScriptId*>(this);
        AnimationManager_SetFlag_004492a0(g_sprt_ctrl, id);
        value = 0;
    }
};
struct Handle4 {
    unsigned int value;
    __declspec(noinline) Ref4 FindChildRef(int script_id);
    __declspec(noinline) void StopAtFrame3();
};

struct AnimationTreeNode {
    AnimationTreeNode* object;
    AnimationTreeNode* next;
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;
};

// A handle to a running animation; zero when there is none.
struct AnimationHandle_00424480 {
    unsigned int value;
};

// The sprite an animation currently shows.
struct AnimationSprite_00424480 {
    unsigned char reserved_00[0x08];
    float left;                          // +0x08
    float top;                           // +0x0C
    unsigned char reserved_10[0x20];
    float height;                        // +0x30
    float width;                         // +0x34
};

// A running animation as this code sees it.
struct AnimationObject_00424480 {
    AnimationObject_00424480* object;    // +0x000: list nodes point at the animation
    AnimationObject_00424480* next;      // +0x004
    unsigned char reserved_008[0x300];
    int* texture;                        // +0x308
    unsigned char reserved_30c[0x88];
    AnimationSprite_00424480* sprite;    // +0x394
};


// A screen rectangle filled from a region of a texture.
struct SpriteRegion_00424480 {
    int reserved_00;
    int texture;                         // +0x04: negative while unbound
    int left;                            // +0x08
    int top;                             // +0x0C
    int width;                           // +0x10
    int height;                          // +0x14
    int source_left;                     // +0x18
    int source_top;                      // +0x1C
    int source_width;                    // +0x20
    int source_height;                   // +0x24
    int state;                           // +0x28

    // Take a texture region; fails once a texture is bound.
    int Set(int new_texture, int new_left, int new_top, int new_width, int new_height,
            int new_source_left, int new_source_top, int new_source_width,
            int new_source_height) {
        if (texture >= 0)
            return -1;
        texture = new_texture;
        left = new_left;
        top = new_top;
        width = new_width;
        height = new_height;
        source_left = new_source_left;
        source_top = new_source_top;
        source_width = new_source_width;
        source_height = new_source_height;
        state = 0;
        return 0;
    }

    // 0x00424480: bind to the sprite an animation currently shows.
    __declspec(noinline) int BindToAnimation(AnimationHandle_00424480 handle,
        int new_left, int new_top, int new_width, int new_height);
};


struct AnimationPool {
    char header[0x68]; Entity objects[4096]; unsigned char occupied[4096]; int next_slot;
    __declspec(noinline) Entity* Allocate();
};
struct AnimationResource_00449870 {
    __declspec(noinline) __declspec(dllexport) void InitializeObject(Entity* object, int index);
};
struct PauseMenuFrame { unsigned int unused; unsigned char flags; };
struct PauseMenuRuntime {
    unsigned char unknown_00[8]; PauseMenuFrame* active_frame;
    unsigned char unknown_0c[8]; int elapsed;
    unsigned char reserved_018[0x58 - 0x18]; unsigned int flags; int replay_mode;
};
struct PauseResourceOwner1 { unsigned char reserved[0x8998]; AnimationResource_00449870* resource; };
struct PauseResourceOwner2 { unsigned char reserved[0x9EC8]; AnimationResource_00449870* resource; };
struct PauseUpdateView {
    int unknown_00; unsigned int phase; unsigned char unknown_08[8];
    int previous_frame; int current_frame; float elapsed; const float* speed; unsigned int timer_flags;
    unsigned char reserved_024[0x1D4 - 0x24]; Handle4 background; Handle4 cursor_animation; Handle4 pause_animation;
    unsigned char reserved_1e0[0x2C0 - 0x1E0]; float saved_speed; AnimationResource_00449870* resource;
    __declspec(noinline) int Update();
};
typedef char PauseBackgroundOffset[offsetof(PauseUpdateView,background)==0x1D4 ? 1:-1];
typedef char PauseSpeedOffset[offsetof(PauseUpdateView,saved_speed)==0x2C0 ? 1:-1];
struct AnimationSecondaryNode { Entity* object; AnimationSecondaryNode* next; AnimationSecondaryNode* previous; };
struct AnimationSecondaryLists {
    unsigned char reserved[0x72DADC]; AnimationSecondaryNode* head; AnimationSecondaryNode* tail;
    unsigned char reserved_72dae4[0x732454 - 0x72DAE4]; unsigned int next_handle;
    __declspec(noinline) Handle4* RegisterSecondaryBack(Handle4* out, Entity* object);
};
extern "C" unsigned char g_globals_flags;
extern "C" unsigned char data_00474e36;
extern "C" unsigned char data_00491ff4;
extern "C" PauseMenuRuntime* g_game;
extern "C" PauseResourceOwner1* g_ascii_manager;
extern "C" PauseResourceOwner2* g_front;
extern "C" float data_00470b68;
extern "C" float data_00470b64;
extern "C" float g_game_speed;
extern "C" char data_0046e0c0[];
extern "C" void __stdcall PauseMenu_Initialize_00422ab0(PauseUpdateView*);
extern "C" void __stdcall PauseMenu_Update_00422c80(PauseUpdateView*);
extern "C" void __stdcall ReplayMenu_Update_004236f0(PauseUpdateView*);
