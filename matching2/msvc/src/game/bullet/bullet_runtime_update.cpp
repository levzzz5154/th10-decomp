// 0x00406240..0x004065B4: update motion, field contacts, bounds, and animation.
// A retirement request, expired bounds, or finished animation clears both
// scheduler links and returns -1. Mode 2 can enter mode 1 during the same tick.
#include "th10/game/bullet_runtime_state.hpp"
#include "th10/game/bullet_runtime_actions.hpp"
#include "th10/game/bullet_reset_anchor.hpp"
#pragma code_seg(".text$00fruntime")
extern "C" int __stdcall BulletRuntimeTick(BulletRuntimeState* state) {
    if (state->flags & 8u) {
        reinterpret_cast<Player2*>(state)->ResetSchedulerLinks();
        return -1;
    }
    switch (state->mode) {
    case 3: {
        MotionVector3 movement = state->velocity * g_game_speed;
        state->position += movement * 0.5f;
        break;
    }
    case 2: {
        MotionVector3 movement = state->velocity * g_game_speed;
        state->position += movement * 0.5f;
        if (!state->animation_progress)
            break;
        state->mode = 1;
        // Transition into the active path within the same tick.
    }
    case 1: {
        reinterpret_cast<ProjectileCommandRuntime*>(state)->Tick();
        if (state->motion_flags) {
            if (state->motion_flags & 1u)
                reinterpret_cast<PlayerAnimationState*>(state)->AdvanceAnimationFrame();
            if (state->motion_flags & 0x10u)
                reinterpret_cast<EffectAccel2*>(state)->Update();
            if (state->motion_flags & 0x20u)
                reinterpret_cast<PlayerDeathShrinkState*>(state)->AdvanceDeathShrink();
            if (state->motion_flags & 0x40u)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->TurnStep();
            if (state->motion_flags & 0x100u)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->EaseStep();
            if (state->motion_flags & 0x80u)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->AimStep();
            if (state->motion_flags & 0x08000c00u)
                reinterpret_cast<BulletRuntimeDeceleration*>(state)->Bounce();
            if (state->motion_flags & 0x04000000u)
                reinterpret_cast<PlayerHomingState*>(state)->HomeTowardTarget();
            if (state->motion_flags & 0x8000u) {
                if (state->immunity_timer.current <= 0)
                    state->motion_flags ^= 0x8000u;
                else
                    state->immunity_timer.Advance(-1.0f);
            }
        }
        state->position += state->velocity * g_game_speed;
        if (state->flags & 2u) {
            int contact = FieldContact004266B0(
                reinterpret_cast<const ContactVector2*>(&state->position),
                reinterpret_cast<TriggerFieldContact*>(g_player),
                reinterpret_cast<const ContactVector2*>(&state->collision_width));
            void* result;
            if (contact == 1) {
                state->mode = 3;
                state->stop_frame = 1;
                if (state->death_animation >= 0)
                    AnimationManager_CreateScreenPositionedPrimary(
                        g_bullet_manager->resource, &result, state->death_animation,
                        reinterpret_cast<const AnimationPosition2*>(&state->position));
            } else if (contact == 2 && !(state->flags & 4u)) {
                state->flags |= 4u;
                AnimationManager_CreateScreenPositionedPrimary(
                    g_bullet_manager->resource, &result, 434,
                    reinterpret_cast<const AnimationPosition2*>(&state->position));
                g_sound_manager.QueuePan(28, state->position.x);
            }
        }
        break;
    }
    }
    if (state->bounds) {
        if (state->motion_flags & 0x00100000u)
            reinterpret_cast<PlayerWrapHorizontalState*>(state)->WrapHorizontal();
        if (state->motion_flags & 0x00200000u)
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
