#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"
#include "th10/math/timer.hpp"

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
    AnimationResource_00449870* resource;    // +0x010
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
    AnimationResource_00449870* resource;
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
extern "C" TriggerResources* data_004776f0;

extern "C" TriggerPlayer* data_004776f4;
extern "C" SoundQueue data_00492590;
struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" void __stdcall LoadScript_0043e710(
    AnimationResource_0043e710*, AnimationObject_0043e710*, int);

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

static __forceinline void SpawnTriggerParticle(AnimationResource_00449870* resource,
        int index, const DispatcherVec3* position) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags = object->flags_35C;
    object->render_bucket = 0;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, index);
    AnimationLookupContext* manager = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    DispatcherRef handle = reinterpret_cast<DispatcherPrimaryLists*>(manager)->RegisterPrimaryBack(object);
    DispatcherSetPosition(manager, position, AnimationScriptId(handle.value));
}
#pragma code_seg(".text$00426cf0_fn")
struct TriggerField_004267f0;
extern "C" __declspec(noinline) void __stdcall ActivateField_00426cf0(TriggerField_004267f0* field) {
    // This view also exposes the embedded animation and timers beyond the
    // fields used by the rotated-region classifier's narrower declaration.
    TriggerAnimationField* target = reinterpret_cast<TriggerAnimationField*>(field);
    target->mode = 4;
    TriggerPosition position(target->position);
    SpawnTriggerParticle(data_004776f0->resource, 0x162, &position);
    for (int i = 0; i < 32; ++i)
        SpawnTriggerParticle(data_004776f0->resource, 0x163, &position);
    target->timer.Set(0);
    if (data_00477810 && !(data_00477810->flags & 0x200))
        data_00492590.Queue(4, 0);
    target->activation_timer.Set(6);
    LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710*>(target->resource),
        reinterpret_cast<AnimationObject_0043e710*>(&target->animation), 0);
    TriggerPlayer* player = data_004776f4;
    if (player->elapsed_frames >= 60) {
        player->pending_state = 0;
        player->flags &= ~2u;
        // Slot 2 retains its pending flag, as in the standalone cleanup.
        for (int i = 0; i < 8; ++i)
            if (i != 2)
                player->entities[i].flags &= ~2u;
    }
}
#pragma code_seg()
