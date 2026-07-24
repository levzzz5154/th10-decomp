#include "th10/game/stage_update.hpp"

#include <cassert>
#include <cstring>

namespace {

int calls[24];
int destroy_requested;

void Call0() { ++calls[0]; }
void Activate() { ++calls[1]; }
void Timer(int index) { ++calls[2 + index]; }
void Refresh(StageUpdateTaskPair*) { ++calls[4]; }
void Effect(int variant) { calls[5] = variant; }
void Spawn(StageContext*) { ++calls[6]; }
int WantsDestroy(void*) { return destroy_requested; }
void Destroy(void*) { ++calls[7]; }
void Free(void*) { ++calls[8]; }
void TickTimer(StageContext*) { ++calls[9]; }
void ClearPending() { ++calls[10]; }

StageUpdateEnv MakeEnv(StageUpdateGlobals* globals,
                       StageUpdateTaskPair* pairs) {
    StageUpdateEnv env = {};
    env.globals = globals;
    env.task_pairs = pairs;
    env.task_pair_count = 2;
    env.enter_transition_lock = Call0;
    env.activate_bullets = Activate;
    env.arm_player_timer = Call0;
    env.start_player_mode = Call0;
    env.reset_thread_timer = Timer;
    env.clear_thread_pending = ClearPending;
    env.stop_player_runtime = Call0;
    env.reset_stage_runtime = Call0;
    env.clear_stage_arena = Call0;
    env.reset_enemy_runtime = Call0;
    env.release_cleanup_chain = Call0;
    env.reset_gameplay_action = Call0;
    env.start_main_ecl = Call0;
    env.initialize_stage_runtime = Call0;
    env.refresh_side_panel = Refresh;
    env.start_stage_music = Call0;
    env.create_delayed_stage_effect = Effect;
    env.reset_player_spawn = Spawn;
    env.player_requests_destroy = WantsDestroy;
    env.destroy_player = Destroy;
    env.free_player = Free;
    env.spawn_transition_effect = Call0;
    env.run_transition_action = Call0;
    env.tick_game = Call0;
    env.update_score_threshold = Call0;
    env.tick_stage_timer = TickTimer;
    return env;
}

void SetFrame(StageContext* context, int frame) {
    std::memcpy(&context->spawn[1], &frame, 4);
}

} // namespace

int main() {
    StageContext context = {};
    StageUpdateGlobals globals = {};
    static unsigned char score_file[12 * 17276] = {};
    globals.score_file = score_file;
    StageTaskNode nodes[5] = {};
    StageUpdateTaskPair pairs[2] = {
        {&nodes[0], &nodes[1]}, {&nodes[2], &nodes[3]},
    };
    StageUpdateEnv env = MakeEnv(&globals, pairs);
    env.player_extra_task = &nodes[4];

    SetFrame(&context, 0);
    assert(StageContext_Update(&context, &env) == 1);
    assert(calls[1] == 1);
    for (StageTaskNode& node : nodes)
        assert((node.flags & 2u) != 0);
    assert(globals.frame_counter_a == 1);
    assert(globals.frame_counter_b == 1);

    std::memset(calls, 0, sizeof(calls));
    context = {};
    context.flags = 8;
    globals.ui_flags = 0x1000;
    SetFrame(&context, 0);
    assert(StageContext_Update(&context, &env) == 1);
    assert(globals.transition_result == 2);

    context = {};
    context.flags = 4;
    SetFrame(&context, 45);
    assert(StageContext_Update(&context, &env) == 1);
    assert((context.flags & 0x80u) != 0);

    context = {};
    context.flags = 0x10;
    SetFrame(&context, 100);
    assert(StageContext_Update(&context, &env) == 3);

    context = {};
    globals.player = &nodes[0];
    destroy_requested = 1;
    SetFrame(&context, 100);
    assert(StageContext_Update(&context, &env) == 1);
    assert(globals.player == 0);
    assert(calls[7] == 1 && calls[8] == 1);
    return 0;
}
