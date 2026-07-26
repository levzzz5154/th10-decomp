#pragma once

#include "th10/game/stage_entry.hpp"

// Dependency-injected reconstruction of the retail 0x00418190 stage
// update/state machine.
struct StageUpdateTaskPair {
    StageTaskNode* update;
    StageTaskNode* draw;
};

struct StageUpdateGlobals {
    unsigned int game_flags;
    unsigned int ui_flags;
    unsigned int descriptor_flags;
    unsigned int transition_mask;
    int transition_result;
    int character;
    int stage;
    int frame_counter_a;
    int frame_counter_b;
    int session_mode;
    int practice_active;
    int game_thread_busy;
    unsigned char* score_file;
    void* player;
};

struct StageUpdateEnv {
    StageUpdateGlobals* globals;
    StageUpdateTaskPair* task_pairs;
    int task_pair_count;
    StageTaskNode* player_extra_task;

    void (*enter_transition_lock)();
    void (*activate_bullets)();
    void (*arm_player_timer)();
    void (*start_player_mode)();
    void (*reset_thread_timer)(int index);
    void (*clear_thread_pending)();
    void (*stop_player_runtime)();
    void (*reset_stage_runtime)();
    void (*clear_stage_arena)();
    void (*reset_enemy_runtime)();
    void (*release_cleanup_chain)();
    void (*reset_gameplay_action)();
    void (*start_main_ecl)();
    void (*initialize_stage_runtime)();
    void (*refresh_side_panel)(StageUpdateTaskPair* pair);
    void (*start_stage_music)();
    void (*create_delayed_stage_effect)(int variant);
    void (*reset_player_spawn)(StageContext* context);
    int (*player_requests_destroy)(void* player);
    void (*destroy_player)(void* player);
    void (*free_player)(void* player);
    void (*spawn_transition_effect)();
    void (*run_transition_action)();
    void (*tick_game)();
    void (*update_score_threshold)();
    void (*tick_stage_timer)(StageContext* context);
};

int StageContext_Update(StageContext* context, const StageUpdateEnv* env);
