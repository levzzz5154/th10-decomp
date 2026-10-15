#define g_sprt_ctrl stage_front_g_sprt_ctrl
#define g_front stage_front_g_front
#define g_globals stage_front_data
#define g_ascii_manager stage_front_data_004776e0
#define g_enemy_ctrl stage_front_g_enemy_ctrl
#define g_player stage_front_data_00477834
#define g_replay stage_front_data_00477838
#define g_score stage_front_data_0047783c
#define g_game_speed stage_front_data_00476f78
#define g_stage_flags stage_front_data_00491fc4
#define g_main_state stage_front_data_00491fb8
#define g_sound_manager stage_front_data_00492590
// Complete 4096-entry pool allocator at 0x00449950, manager ESI and Entity* result EAX.
#include "front_view.hpp"

#pragma code_seg(".text$00449950_fn")
Entity *FrontAnimationPool::Allocate() {
    int slot = next_slot;
    Entity *object = &objects[slot];
    if (occupied[slot]) {
        slot = (slot + 1) % 4096;
        next_slot = slot;
        object = &objects[slot];
        if (occupied[slot]) {
            Entity *block = (Entity *)operator new(sizeof(Entity));
            Entity *created = block != 0 ? Entity_Constructor(block) : (Entity *)0;
            object = created;
            Entity_Init(created);
        } else {
            occupied[slot] = 1;
        }
    } else {
        occupied[slot] = 1;
    }
    next_slot = (next_slot + 1) % 4096;
    return object;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
