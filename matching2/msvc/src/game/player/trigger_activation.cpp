#include "th10/game/pause_result_open/dispatcher_contract.hpp"
#include "th10/math/timer.hpp"
#include "th10/game/player.hpp"

// The screen position of the activation animations. A value constructor keeps
// all three components together while adding the playfield's screen offset.
struct TriggerPosition : DispatcherVec3 {
    TriggerPosition(const DispatcherVec3& source) {
        x = source.x + 224.0f;
        y = source.y + 16.0f;
        z = source.z;
    }
};
struct TriggerAnimationField {
    unsigned char reserved000[0x10];
    AnimationBank* resource;    // +0x010
    Entity animation;                       // +0x014
    DispatcherVec3 position;                // +0x3C0
    unsigned char reserved3cc[0x458 - 0x3cc];
    int mode;                               // +0x458
    unsigned char reserved45c[0x474 - 0x45c];
    OpenTimer timer;                        // +0x474
    unsigned char reserved488[0x430c - 0x488];
    OpenTimer activation_timer;             // +0x430C
};
struct TriggerResources {
    unsigned char reserved000[0x3e0b50];
    AnimationBank* resource;
};
struct TriggerPlayerEntity {
    unsigned char reserved000[0x378];
    unsigned int flags;
    unsigned char reserved37c[0x3ac - 0x37c];
};
struct TriggerPlayer {
    unsigned char reserved000[0x75c];
    TriggerPlayerEntity entities[8];         // +0x75C, stride 0x3AC
    unsigned char reserved24bc[0x3738 - 0x24bc];
    int elapsed_frames;                      // +0x3738
    unsigned char reserved373c[0x378c - 0x373c];
    unsigned int flags;                      // +0x378C
    int pending_state;                       // +0x3790
};
extern "C" TriggerResources* g_bullet_manager;

extern "C" TriggerPlayer* g_card;
extern "C" SoundQueue g_sound_manager;
struct AnimationResourceFile;
struct AnimationObjectFile;
extern "C" void __stdcall LoadScript2(
    AnimationResourceFile*, AnimationObjectFile*, int);

typedef char CheckTriggerAnimation[offsetof(TriggerAnimationField, animation) == 0x14 ? 1 : -1];
typedef char CheckTriggerPosition[offsetof(TriggerAnimationField, position) == 0x3c0 ? 1 : -1];
typedef char CheckTriggerMode[offsetof(TriggerAnimationField, mode) == 0x458 ? 1 : -1];
typedef char CheckTriggerTimer[offsetof(TriggerAnimationField, timer) == 0x474 ? 1 : -1];
typedef char CheckTriggerActivationTimer[
    offsetof(TriggerAnimationField, activation_timer) == 0x430c ? 1 : -1];
typedef char CheckTriggerPlayerEntitySize[sizeof(TriggerPlayerEntity) == 0x3ac ? 1 : -1];
typedef char CheckTriggerPlayerFrames[offsetof(TriggerPlayer, elapsed_frames) == 0x3738 ? 1 : -1];
typedef char CheckTriggerPlayerFlags[offsetof(TriggerPlayer, flags) == 0x378c ? 1 : -1];
typedef char CheckTriggerPlayerPending[offsetof(TriggerPlayer, pending_state) == 0x3790 ? 1 : -1];

__declspec(noinline) void DispatcherSetPosition(
    AnimationLookupContext*, const DispatcherVec3*, AnimationScriptId);

static __forceinline void SpawnTriggerParticle(AnimationBank* resource,
        int index, const DispatcherVec3* position) {
    Entity* object = reinterpret_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags = object->flags_35C;
    object->render_bucket = 0;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, index);
    AnimationLookupContext* manager = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    DispatcherRef handle = reinterpret_cast<DispatcherPrimaryLists*>(manager)->RegisterPrimaryBack(object);
    DispatcherSetPosition(manager, position, AnimationScriptId(handle.value));
}
#pragma code_seg(".text$00426cf0_fn")
extern "C" __declspec(noinline) void __stdcall Player_Hit(Player* player) {
    // Retail sets the two timers through an inline Set that stores in a
    // different order from FrameTimer::Set; this view keeps that copy.
    TriggerAnimationField* target = reinterpret_cast<TriggerAnimationField*>(player);
    target->mode = 4;
    TriggerPosition position(target->position);
    SpawnTriggerParticle(g_bullet_manager->resource, 0x162, &position);
    for (int i = 0; i < 32; ++i)
        SpawnTriggerParticle(g_bullet_manager->resource, 0x163, &position);
    target->timer.Set(0);
    if (g_game && !(g_game->flags & 0x200))
        g_sound_manager.Queue(4, 0);
    target->activation_timer.Set(6);
    LoadScript2(reinterpret_cast<AnimationResourceFile*>(target->resource),
        reinterpret_cast<AnimationObjectFile*>(&target->animation), 0);
    TriggerPlayer* state = g_card;
    if (state->elapsed_frames >= 60) {
        state->pending_state = 0;
        state->flags &= ~2u;
        // Slot 2 retains its pending flag, as in the standalone cleanup.
        for (int i = 0; i < 8; ++i)
            if (i != 2)
                state->entities[i].flags &= ~2u;
    }
}
#pragma code_seg()
