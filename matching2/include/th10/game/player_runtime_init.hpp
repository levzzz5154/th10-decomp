#pragma once

#include <cstdint>

struct PlayerRuntimeObject {
    float speed;
    float vertical_speed;
    float horizontal_speed;
};

struct PlayerRuntimeTimer {
    int target;
    int current;
    int previous;
    const float* speed;
    uint32_t flags;
};

struct PlayerRuntimeState {
    void* animation_archive;
    void* update_task;
    void* draw_task;
    PlayerRuntimeObject* player_object;
    float position[3];
    int score_seed;
    int random_values[4];
    int history[33][2];
    PlayerRuntimeTimer movement_timer;
    PlayerRuntimeTimer focus_timer;
    PlayerRuntimeTimer spawn_timer;
    float hitbox_half[3];
    float item_half[3];
    float graze_half[3];
    float hitbox_bounds[6];
    float item_bounds[6];
    float graze_bounds[6];
    float graze_bounds_copy[6];
    int spawn_frames;
};

struct PlayerRuntimeTables {
    float object_speed[2];
    float object_vertical_speed[2];
    float object_horizontal_speed[2];
    float hitbox_x[2];
    float item_x[2];
    float graze_x[2];
};

struct PlayerRuntimeInitHooks {
    void* context;
    float frame_speed;
    void* reused_player;
    void* (*load_animation)(void* context, int slot, const char* name);
    PlayerRuntimeObject* (*create_player_object)(void* context);
    void* (*register_task)(void* context, int kind,
                           PlayerRuntimeState* state);
    void (*initialize_animation)(void* context, PlayerRuntimeState* state,
                                 void* archive);
    int (*random_int)(void* context);
    void (*report_error)(void* context, const char* resource);
    void (*refresh_derived)(void* context, PlayerRuntimeState* state);
};

// 0x004247F0 - Initialize the player runtime. The final 0x00426F70 call is
// exposed through refresh_derived; it has no return value or cleanup branch.
int PlayerRuntime_Initialize(PlayerRuntimeState* state, int character,
                             const PlayerRuntimeTables* tables,
                             const PlayerRuntimeInitHooks* hooks);

struct LargePlayerRuntimeBindings {
    void* (*create_player_object)();
    void (*initialize_animation)(void* state, void* archive);
    int (*random_int)();
    void (*refresh_derived)(void* state);
};

void LargePlayerRuntime_SetBindings(
    const LargePlayerRuntimeBindings* bindings);
void* LargePlayerRuntime_Construct(void* state);
int LargePlayerRuntime_Initialize(void* state);
