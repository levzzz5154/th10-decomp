#include "th10/game/stage_update.hpp"

#include <cstring>

namespace {

const int kScoreRecordStride = 17276;
const int kFramesPlayedOffset = 0x4CC;

int StageFrame(const StageContext* context) {
    int value;
    // Retail +0x14 is the second word in the spawn/timer block. Address the
    // typed member so native 64-bit validation does not corrupt a pointer.
    std::memcpy(&value, &context->spawn[1], 4);
    return value;
}

void Kill(StageTaskNode* node) {
    if (node)
        node->flags |= 2u;
}

void ResetForStageStart(StageContext* context, const StageUpdateEnv* env,
                        bool delayed) {
    StageUpdateGlobals* globals = env->globals;
    context->flags &= ~0x800u;
    env->stop_player_runtime();
    env->reset_stage_runtime();
    env->clear_stage_arena();
    env->reset_enemy_runtime();
    env->release_cleanup_chain();
    globals->frame_counter_a = 0;
    globals->frame_counter_b = 0;
    env->reset_gameplay_action();
    env->start_main_ecl();
    env->initialize_stage_runtime();

    for (int index = 0; index < env->task_pair_count; ++index) {
        Kill(env->task_pairs[index].update);
        Kill(env->task_pairs[index].draw);
    }
    Kill(env->player_extra_task);
    if (env->task_pair_count > 1)
        env->refresh_side_panel(&env->task_pairs[1]);

    if (delayed) {
        env->create_delayed_stage_effect(
            (globals->descriptor_flags & 0x10u) != 0 ? 4 : 3);
        env->start_stage_music();
        env->reset_thread_timer(1);
        env->clear_thread_pending();
        env->reset_player_spawn(context);
    } else {
        if ((globals->game_flags & 0x20u) == 0)
            env->start_stage_music();
        env->reset_thread_timer(0);
        env->reset_thread_timer(1);
        env->clear_thread_pending();
    }
}

} // namespace

// Semantic reconstruction 0x00418190 - main stage update state machine.
int StageContext_Update(StageContext* context, const StageUpdateEnv* env) {
    StageUpdateGlobals* globals = env->globals;
    const int frame = StageFrame(context);

    if (frame == 0) {
        if ((context->flags & 8u) != 0) {
            env->enter_transition_lock();
            globals->transition_result =
                ((~(globals->ui_flags >> 12)) & 1u) | 2u;
            return 1;
        }
        env->activate_bullets();
        if (globals->player != 0) {
            env->arm_player_timer();
            env->start_player_mode();
            context->flags |= 0x800u;
            env->reset_thread_timer(1);
        } else {
            ResetForStageStart(context, env, false);
        }
    } else if (frame == 30 && (context->flags & 0x800u) != 0) {
        ResetForStageStart(context, env, true);
    }

    if (globals->player != 0 &&
        env->player_requests_destroy(globals->player)) {
        void* player = globals->player;
        env->destroy_player(player);
        env->free_player(player);
        globals->player = 0;
    }

    if ((context->flags & 4u) != 0) {
        context->flags |= 0x80u;
        return 1;
    }

    env->enter_transition_lock();
    if ((globals->game_flags & 0x20u) != 0) {
        if ((globals->transition_mask & 0x160Bu) != 0 ||
            (context->flags & 0x70u) != 0) {
            globals->transition_result =
                (globals->ui_flags & 0x1000u) != 0 ? 2 : 4;
        }
        if (frame == 0xB7C)
            env->spawn_transition_effect();
        else if (frame == 3000)
            env->run_transition_action();
    }

    env->tick_game();
    if ((context->flags & 0x70u) != 0)
        return 3;

    if (globals->session_mode != 1 && globals->score_file != 0) {
        unsigned char* slot =
            globals->score_file +
            kScoreRecordStride *
                (3 * globals->character + globals->stage) +
            kFramesPlayedOffset;
        int frames_played = 0;
        std::memcpy(&frames_played, slot, 4);
        if (frames_played < 215999999) {
            ++frames_played;
            std::memcpy(slot, &frames_played, 4);
        }
    }
    if (!globals->practice_active && !globals->game_thread_busy &&
        frame >= 90) {
        env->update_score_threshold();
    }
    ++globals->frame_counter_a;
    ++globals->frame_counter_b;
    env->tick_stage_timer(context);
    return 1;
}
