#include "th10/math/timer.hpp"

#include <stddef.h>

// Globals used by the retail player update.
extern "C" void* data_00491c10;
extern "C" void* data_004776f4;
extern "C" int data_00474c68;
extern "C" float data_00470b0c;
extern "C" float data_00470afc;
extern "C" float data_00470d34;
extern "C" float data_00470b4c;
extern "C" float data_00470b48;
extern "C" float data_00470b68;
extern "C" float data_00470b64;

struct AnimationNode_00405750;

struct AnimationChildLink_00405750 {
    AnimationNode_00405750* node;       // +0x00
    AnimationChildLink_00405750* next;  // +0x04
};

struct AnimationNode_00405750 {
    unsigned char unknown_000[0x14];
    AnimationChildLink_00405750* children_014;
    int child_count_018;
    unsigned char unknown_01c[0x24];
    float value_040;
    unsigned char unknown_044[0x2FC];
    float position_340[3];
};

// The lookup routine's first fastcall input is unused by its body.  At this
// call site that register still contains the player pointer; the manager is
// in EDX and the animation handle is the stack argument.
extern "C" AnimationNode_00405750* __fastcall AnimationManager_Find_004491c0(
    void* ignored, void* manager, int animation_handle);

// DrawPlayer is an existing leaf with a private ESI receiver.  This source
// keeps the helper edge; its register-only input is not expressible in an
// ordinary function prototype, so the native-LTCG context is an ABI candidate
// rather than proof of the call-site register assignment.
extern "C" void __cdecl asm_Player_Draw_00405ac0();

struct PlayerUpdate_00405750 {
    unsigned char unknown_000[0x14];
    FrameTimer timer_014;
    int active_state_028;
    int animation_handle_02c;
    float position_030[3];
    float collision_radius_03c;
    float value_040;
    int value_044;

};

typedef char AnimationNode_value_offset_must_be_40[
    offsetof(AnimationNode_00405750, value_040) == 0x40 ? 1 : -1];
typedef char AnimationNode_position_offset_must_be_340[
    offsetof(AnimationNode_00405750, position_340) == 0x340 ? 1 : -1];
typedef char PlayerUpdate_timer_offset_must_be_14[
    offsetof(PlayerUpdate_00405750, timer_014) == 0x14 ? 1 : -1];
typedef char PlayerUpdate_state_offset_must_be_28[
    offsetof(PlayerUpdate_00405750, active_state_028) == 0x28 ? 1 : -1];
typedef char PlayerUpdate_position_offset_must_be_30[
    offsetof(PlayerUpdate_00405750, position_030) == 0x30 ? 1 : -1];

static __forceinline void SetAnimationPosition_00405750(
    AnimationNode_00405750* animation, const float position[3]) {
    animation->position_340[0] = position[0];
    animation->position_340[1] = position[1];
    animation->position_340[2] = position[2];

    // 0x004492F0 also propagates the position through the linked children
    // when this node has no children of its own.
    if (animation->child_count_018 == 0) {
        for (AnimationChildLink_00405750* link = animation->children_014;
             link != 0; link = link->next) {
            AnimationNode_00405750* child = link->node;
            child->position_340[0] = position[0];
            child->position_340[1] = position[1];
            child->position_340[2] = position[2];
        }
    }
}

static __forceinline void TickPlayerTimer_00405750(FrameTimer* timer) {
    timer->previous = timer->current;
    const float speed = *timer->speed;
    if (speed > data_00470b68 && speed < data_00470b64) {
        ++timer->current;
        timer->elapsed += 1.0f;
    } else {
        timer->elapsed += speed;
        timer->current = static_cast<int>(timer->elapsed);
    }
}

#pragma code_seg(".text$01update")
extern "C" __declspec(noinline) int __fastcall UpdatePlayer_00405750(
    PlayerUpdate_00405750* player) {
    if (player->active_state_028 == 0) {
        return 1;
    }

    if (player->active_state_028 == 1) {
        AnimationNode_00405750* animation = AnimationManager_Find_004491c0(
            player, data_00491c10, player->animation_handle_02c);
        if (animation == 0) {
            player->animation_handle_02c = 0;
            player->active_state_028 = 0;
            return 1;
        }

        unsigned char* player_state =
            static_cast<unsigned char*>(data_004776f4);
        const int input_state =
            *reinterpret_cast<int*>(player_state + 0x3788);
        const bool focused =
            (player_state[0x378C] & 1) != 0 &&
            ((input_state >= 0x5D && input_state <= 0x60) ||
             input_state == 0x6D);

        float speed;
        if (focused) {
            speed = data_00470b0c;
        } else if (data_00474c68 == 0) {
            speed = data_00470afc;
        } else {
            speed = data_00470d34;
        }
        player->position_030[1] = player->position_030[1] - speed;

        const float render_position[3] = {
            player->position_030[0] + data_00470b4c,
            player->position_030[1] + data_00470b48,
            player->position_030[2]
        };
        SetAnimationPosition_00405750(animation, render_position);
        player->collision_radius_03c = animation->value_040;

        asm_Player_Draw_00405ac0();
    }

    TickPlayerTimer_00405750(&player->timer_014);
    return 1;
}
#pragma code_seg()
