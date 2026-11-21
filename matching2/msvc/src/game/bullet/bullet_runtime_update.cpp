// 0x00406240..0x004065B4: update motion, field contacts, bounds, and animation.
// A retirement request, expired bounds, or finished animation clears both
// scheduler links and returns -1. Mode 2 can enter mode 1 during the same tick.
#include "th10/game/bullet_runtime_state.hpp"
#include "th10/game/bullet_runtime_actions.hpp"
#include "th10/game/bullet_reset_anchor.hpp"
enum BulletRuntimeMode {
    BULLET_MODE_ACTIVE = 1,
    BULLET_MODE_SPAWNING = 2,
    BULLET_MODE_CANCELLED = 3
};

enum BulletRuntimeFlags {
    BULLET_FLAG_CAN_HIT_PLAYER = 0x02u,
    BULLET_FLAG_GRAZED = 0x04u,
    BULLET_FLAG_RETIRE = 0x08u
};

enum BulletRuntimeMotionFlag {
    BULLET_MOTION_SPEED_CURVE = 0x00000001u,
    BULLET_MOTION_ACCEL_VECTOR = 0x00000010u,
    BULLET_MOTION_ANGULAR_ACCEL = 0x00000020u,
    BULLET_MOTION_TURN_STEP = 0x00000040u,
    BULLET_MOTION_AIM_STEP = 0x00000080u,
    BULLET_MOTION_EASE_STEP = 0x00000100u,
    BULLET_MOTION_WAIT = 0x00008000u,
    BULLET_MOTION_WRAP_HORIZONTAL = 0x00100000u,
    BULLET_MOTION_WRAP_VERTICAL = 0x00200000u,
    BULLET_MOTION_HOME = 0x04000000u,
    BULLET_MOTION_BOUNCE_ANY = 0x08000C00u
};

enum BulletContactKind {
    BULLET_CONTACT_HIT = 1,
    BULLET_CONTACT_GRAZE = 2
};

enum BulletRuntimeAssets {
    BULLET_ANM_GRAZE_SPARK = 434,
    BULLET_SFX_GRAZE = 28
};

#pragma code_seg(".text$00fruntime")
extern "C" int __stdcall BulletRuntimeTick(BulletRuntimeState* state) {
    if (state->flags & BULLET_FLAG_RETIRE) {
        reinterpret_cast<Player2*>(state)->ResetSchedulerLinks();
        return -1;
    }
    switch (state->mode) {
    case BULLET_MODE_CANCELLED: {
        MotionVector3 movement = state->velocity * g_game_speed;
        state->position += movement * 0.5f;
        break;
    }
    case BULLET_MODE_SPAWNING: {
        MotionVector3 movement = state->velocity * g_game_speed;
        state->position += movement * 0.5f;
        if (!state->animation_progress)
            break;
        state->mode = BULLET_MODE_ACTIVE;
        // Transition into the active path within the same tick.
    }
    case BULLET_MODE_ACTIVE: {
        reinterpret_cast<ProjectileCommandRuntime*>(state)->Tick();
        if (state->motion_flags) {
            if (state->motion_flags & BULLET_MOTION_SPEED_CURVE)
                reinterpret_cast<PlayerAnimationState*>(state)->AdvanceAnimationFrame();
            if (state->motion_flags & BULLET_MOTION_ACCEL_VECTOR)
                reinterpret_cast<EffectAccel2*>(state)->Update();
            if (state->motion_flags & BULLET_MOTION_ANGULAR_ACCEL)
                reinterpret_cast<PlayerDeathShrinkState*>(state)->AdvanceDeathShrink();
            if (state->motion_flags & BULLET_MOTION_TURN_STEP)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->TurnStep();
            if (state->motion_flags & BULLET_MOTION_EASE_STEP)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->EaseStep();
            if (state->motion_flags & BULLET_MOTION_AIM_STEP)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->AimStep();
            if (state->motion_flags & BULLET_MOTION_BOUNCE_ANY)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->Bounce();
            if (state->motion_flags & BULLET_MOTION_HOME)
                reinterpret_cast<PlayerHomingState*>(state)->HomeTowardTarget();
            if (state->motion_flags & BULLET_MOTION_WAIT) {
                if (state->immunity_timer.current <= 0)
                    state->motion_flags ^= BULLET_MOTION_WAIT;
                else
                    state->immunity_timer.Advance(-1.0f);
            }
        }
        state->position += state->velocity * g_game_speed;
        if (state->flags & BULLET_FLAG_CAN_HIT_PLAYER) {
            int contact = FieldContact004266B0(
                reinterpret_cast<const ContactVector2*>(&state->position),
                reinterpret_cast<TriggerFieldContact*>(g_player),
                reinterpret_cast<const ContactVector2*>(&state->collision_width));
            void* result;
            if (contact == BULLET_CONTACT_HIT) {
                state->mode = BULLET_MODE_CANCELLED;
                state->stop_frame = 1;
                if (state->death_animation >= 0)
                    AnimationManager_CreateScreenPositionedPrimary(
                        g_bullet_manager->resource, &result, state->death_animation,
                        reinterpret_cast<const AnimationPosition2*>(&state->position));
            } else if (contact == BULLET_CONTACT_GRAZE && !(state->flags & BULLET_FLAG_GRAZED)) {
                state->flags |= BULLET_FLAG_GRAZED;
                AnimationManager_CreateScreenPositionedPrimary(
                    g_bullet_manager->resource, &result, BULLET_ANM_GRAZE_SPARK,
                    reinterpret_cast<const AnimationPosition2*>(&state->position));
                g_sound_manager.QueuePan(BULLET_SFX_GRAZE, state->position.x);
            }
        }
        break;
    }
    }
    if (state->bounds) {
        if (state->motion_flags & BULLET_MOTION_WRAP_HORIZONTAL)
            reinterpret_cast<PlayerWrapHorizontalState*>(state)->WrapHorizontal();
        if (state->motion_flags & BULLET_MOTION_WRAP_VERTICAL)
            reinterpret_cast<PlayerWrapHorizontalState*>(state)->WrapVertical();
        if (state->bounds_grace <= 0 &&
            reinterpret_cast<PlayfieldPoint*>(&state->position)
                ->OutsidePlayfield(state->bounds->extent_34, state->bounds->extent_30)) {
            reinterpret_cast<Player2*>(state)->ResetSchedulerLinks();
            return -1;
        }
    }
    if (state->countdown)
        --state->countdown;
    if (state->bounds_grace > 0)
        --state->bounds_grace;
    int result = RunAnimationVm(state->animation);
    if (result) {
        reinterpret_cast<Player2*>(state)->ResetSchedulerLinks();
        return -1;
    }
    return result;
}
#pragma code_seg()
