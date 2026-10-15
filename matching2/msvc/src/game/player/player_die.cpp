// 0x004269D0: the player dies: take a life and some power, enter the dying
// state with 180 frames of invulnerability, drop the options and show the
// lives-left caution.
#include "th10/game/pause_result_open_004231d0/open_state.hpp"
#include "th10/game/hint_data_create.hpp"
#include "th10/game/player.hpp"
#include "th10/game/player_die.hpp"

struct AnimationRecord_00413790 {
    unsigned int flags_0000;             // +0x000
    unsigned char pad_0004[0x3AC - 4];
};

struct AnimationManager_00413790 {
    unsigned char pad_0000[0x4CDC];
    AnimationRecord_00413790 records_4cdc[9];
    __declspec(noinline) void SetActiveCount(int count);
};

struct TimeoutAnimation;
struct TimeoutAnimationLink {
    TimeoutAnimation* object;
    TimeoutAnimationLink* next;
};
struct TimeoutAnimation {
    int id;
    unsigned char reserved004[0x14 - 4];
    TimeoutAnimationLink* children;
    int children_flagged;
    unsigned char reserved01c[0x304 - 0x1c];
    short stop_frame;
};
struct TimeoutAnimationManager {
    unsigned char reserved000[0x72dad4];
    TimeoutAnimationLink* primary;
    int reserved72dad8;
    TimeoutAnimationLink* secondary;
    __forceinline TimeoutAnimation* Find(int id) {
        if (!id)
            return 0;
        for (TimeoutAnimationLink* node = primary; node; node = node->next)
            if (node->object->id == id)
                return node->object;
        for (TimeoutAnimationLink* node = secondary; node; node = node->next)
            if (node->object->id == id)
                return node->object;
        return 0;
    }
};
// Stop an animation and its children at frame 1, looked up by handle.
static __forceinline void StopAtFrame1(int value, TimeoutAnimationManager* manager) {
    TimeoutAnimation* object = manager->Find(value);
    if (object) {
        object->stop_frame = 1;
        if (!object->children_flagged)
            for (TimeoutAnimationLink* child = object->children; child; child = child->next)
                child->object->stop_frame = 1;
    }
}
struct TimeoutPlayerEntity {
    unsigned char reserved000[0x378];
    unsigned int flags;
    unsigned char reserved37c[0x3ac - 0x37c];
};
struct TimeoutPlayer {
    unsigned char reserved000[0x75c];
    TimeoutPlayerEntity entities[8];
    unsigned char reserved24bc[0x3738 - 0x24bc];
    int elapsed_frames;
    unsigned char reserved373c[0x378c - 0x373c];
    unsigned int flags;
    int pending_state;
};
struct TimeoutMode {
    unsigned char reserved000[0x10];
    int mode;
};
extern "C" {
    extern int data_00474c4c;
    extern int data_00474c70;
    extern int data_00474c98;
    extern TimeoutMode* data_00477838;
    extern Hint* g_hint;
    extern TimeoutPlayer* g_card;
    extern const char g_timeout_caution[];
}
struct AnimationResource_0043e710;
struct AnimationObject_0043e710;
extern "C" void __stdcall LoadScript_0043e710(AnimationResource_0043e710*,AnimationObject_0043e710*, int);

typedef char TimeoutCountRecordSize[sizeof(AnimationRecord_00413790) == 0x3AC ? 1 : -1];
typedef char TimeoutCountRecordsOffset[offsetof(AnimationManager_00413790, records_4cdc) == 0x4CDC ? 1 : -1];
typedef char TimeoutAnimationChildren[offsetof(TimeoutAnimation, children) == 0x14 ? 1 : -1];
typedef char TimeoutAnimationChildrenFlag[offsetof(TimeoutAnimation, children_flagged) == 0x18 ? 1 : -1];
typedef char TimeoutAnimationStopFrame[offsetof(TimeoutAnimation, stop_frame) == 0x304 ? 1 : -1];
typedef char TimeoutPrimaryList[offsetof(TimeoutAnimationManager, primary) == 0x72DAD4 ? 1 : -1];
typedef char TimeoutSecondaryList[offsetof(TimeoutAnimationManager, secondary) == 0x72DADC ? 1 : -1];
typedef char TimeoutPlayerEntitySize[sizeof(TimeoutPlayerEntity) == 0x3AC ? 1 : -1];
typedef char TimeoutPlayerEntityFlags[offsetof(TimeoutPlayerEntity, flags) == 0x378 ? 1 : -1];
typedef char TimeoutPlayerEntities[offsetof(TimeoutPlayer, entities) == 0x75C ? 1 : -1];
typedef char TimeoutPlayerFrames[offsetof(TimeoutPlayer, elapsed_frames) == 0x3738 ? 1 : -1];
typedef char TimeoutPlayerFlags[offsetof(TimeoutPlayer, flags) == 0x378C ? 1 : -1];
typedef char TimeoutPlayerState[offsetof(TimeoutPlayer, pending_state) == 0x3790 ? 1 : -1];

// The timer store order of this function (current, elapsed, previous).
static __forceinline void SetTimer(FrameTimer& timer, int frame) {
    if (!(timer.flags & 1)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0.0f;
        timer.speed = &data_00476f78;
        timer.flags |= 1;
    }
    timer.current = frame;
    timer.elapsed = (float)frame;
    timer.previous = frame - 1;
}

#pragma code_seg(".text$004269d0_fn")
extern "C" __declspec(noinline) void __stdcall Player_Die(Player* player) {
    // Retain the option-array base across the arithmetic and helper calls.
    PlayerOption* options = player->options;
    int power = data_00474c4c;
    int remaining = data_00474c70 - 1;
    // Preserve the signed fixed-point intermediate: multiplying and dividing
    // by ten cannot be cancelled for values whose intermediate wraps.
    power += ((power - 5000) / -3 * 10) / 10;
    data_00474c70 = remaining;
    data_00474c4c = power;
    if (power < 5000)
        data_00474c4c = 5000;
    if (remaining >= 0)
        reinterpret_cast<AnimationManager_00413790*>(g_front)->SetActiveCount(remaining);
    player->state = PLAYER_DYING;
    SetTimer(player->state_timer, 0);
    SetTimer(player->invulnerability_timer, 180);
    LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710*>(player->animation_file),
        reinterpret_cast<AnimationObject_0043e710*>(&player->sprite), 0);
    TimeoutAnimationManager* manager =
        reinterpret_cast<TimeoutAnimationManager*>(g_sprt_ctrl);
    unsigned int* handles = &options[0].animation;
    for (int i = 0; i < 4; ++i) {
        PlayerOption* option = reinterpret_cast<PlayerOption*>(
            reinterpret_cast<char*>(handles) - offsetof(PlayerOption, animation));
        // Capture the first handle before clearing the option.
        int first = handles[0];
        option->active = 0;
        StopAtFrame1(first, manager);
        StopAtFrame1(handles[1], manager);
        handles = reinterpret_cast<unsigned int*>(
            reinterpret_cast<char*>(handles) + sizeof(PlayerOption));
    }
    player->option_count = 0;
    if (data_00477838->mode != 1)
        HintData_CreateUrgent_00424650(g_hint, g_timeout_caution,
            reinterpret_cast<const HintDataPosition*>(&player->position));
    TimeoutPlayer* gauge = g_card;
    if (gauge->elapsed_frames >= 60) {
        gauge->pending_state = 0;
        gauge->flags &= ~2u;
        for (int i = 0; i < 8; ++i)
            if (i != 2)
                gauge->entities[i].flags &= ~2u;
    }
    data_00474c98 -= 1024;
    if (data_00474c98 > 1024)
        data_00474c98 = 1024;
    else if (data_00474c98 < -1024)
        data_00474c98 = -1024;
}
#pragma code_seg()
