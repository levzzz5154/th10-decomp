// 0x00404450 (214 bytes): enable the stage's three tasks, then start one
// animation script for every quad of every stage object and remember which
// entity each quad got.
#include "th10/game/entity.hpp"

struct AnimationResourceFile;
void __stdcall Entity_StartScript(AnimationResourceFile* resource,
                                           Entity* entity, int script);

struct StageTask {
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

struct StageFile {
    short object_count;
};

struct Stage_00404450 {
    unsigned char reserved_0000[8];
    StageTask* update_task;            // +0x08
    StageTask* draw_task;              // +0x0c
    StageFile* file;                   // +0x10
    StageObject_00404450** objects;             // +0x14
    unsigned char reserved_0018[4];
    int initial_value_1c;                       // +0x1c
    unsigned char reserved_0020[0x4c - 0x20];
    int value_4c;                               // +0x4c
    unsigned char reserved_0050[0x178 - 0x50];
    AnimationResourceFile* animation;      // +0x178
    Entity* quad_entities;                      // +0x17c
    unsigned char reserved_0180[0x2a40 - 0x180];
    StageTask* after_draw_task;        // +0x2a40
};

#pragma code_seg(".text$00m_stage")
__declspec(noinline) void __stdcall Stage_StartQuadScripts(Stage_00404450* stage) {
    stage->update_task->flags |= 2;
    stage->draw_task->flags |= 2;
    stage->after_draw_task->flags |= 2;
    int entity_index = 0;
    for (int index = 0; index < stage->file->object_count; ++index) {
        stage->objects[index]->active = 1;
        StageQuad_00404450* quad = stage->objects[index]->quads;
        while (quad->type >= 0) {
            Entity_StartScript(stage->animation, &stage->quad_entities[entity_index],
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
