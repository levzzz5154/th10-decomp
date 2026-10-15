#define g_sprt_ctrl stage_quad_g_sprt_ctrl
#define g_front stage_quad_g_front
#define g_globals stage_quad_data_00474c40
#define g_ascii_manager stage_quad_data_004776e0
#define g_enemy_ctrl stage_quad_g_enemy_ctrl
#define g_player stage_quad_data_00477834
#define g_replay stage_quad_data_00477838
#define g_score stage_quad_data_0047783c
#define g_game_speed stage_quad_data_00476f78
#define g_stage_flags stage_quad_data_00491fc4
#define g_main_state stage_quad_data_00491fb8
#define g_sound_manager stage_quad_data_00492590
// 0x00404450 (214 bytes): enable the stage's three tasks, then start one
// animation script for every quad of every stage object and remember which
// entity each quad got.
#include "th10/game/entity.hpp"

struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);

struct StageTask_00404450 {
    int priority;
    unsigned int flags;                 // +0x04, bit 1: enabled
};

// One drawable piece of a stage object; the list ends at a negative type.
struct StageQuad_00404450 {
    short type;                         // +0x00
    short size;                         // +0x02, bytes to the next quad
    short script;                       // +0x04
    short entity_index;                 // +0x06, filled in here
};

struct StageObject_00404450 {
    unsigned char reserved_00[3];
    unsigned char active;               // +0x03
    unsigned char reserved_04[0x18];
    StageQuad_00404450 quads[1];        // +0x1c
};

struct StageFile_00404450 {
    short object_count;
};

struct Stage_00404450 {
    unsigned char reserved_0000[8];
    StageTask_00404450* update_task;            // +0x08
    StageTask_00404450* draw_task;              // +0x0c
    StageFile_00404450* file;                   // +0x10
    StageObject_00404450** objects;             // +0x14
    unsigned char reserved_0018[4];
    int initial_value_1c;                       // +0x1c
    unsigned char reserved_0020[0x4c - 0x20];
    int value_4c;                               // +0x4c
    unsigned char reserved_0050[0x178 - 0x50];
    AnimationResource_0043e710* animation;      // +0x178
    Entity* quad_entities;                      // +0x17c
    unsigned char reserved_0180[0x2a40 - 0x180];
    StageTask_00404450* after_draw_task;        // +0x2a40
};

#pragma code_seg(".text$00404450_fn")
__declspec(noinline) void __stdcall Stage_StartQuadScripts_00404450(Stage_00404450* stage) {
    stage->update_task->flags |= 2;
    stage->draw_task->flags |= 2;
    stage->after_draw_task->flags |= 2;
    int entity_index = 0;
    for (int index = 0; index < stage->file->object_count; ++index) {
        stage->objects[index]->active = 1;
        StageQuad_00404450* quad = stage->objects[index]->quads;
        while (quad->type >= 0) {
            Entity_StartScript_00404f30(stage->animation, &stage->quad_entities[entity_index],
                                        quad->script);
            quad->entity_index = static_cast<short>(entity_index);
            ++entity_index;
            quad = reinterpret_cast<StageQuad_00404450*>(
                reinterpret_cast<char*>(quad) + quad->size);
        }
    }
    stage->value_4c = stage->initial_value_1c;
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
