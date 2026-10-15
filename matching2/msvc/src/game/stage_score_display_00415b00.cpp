// 0x00415B00: construct the per-stage score display, then clear live effects.
#include <string.h>
#include "th10/game/stage_score_display_00415b00.hpp"
#include "th10/game/entity_script_start.hpp"

static __forceinline SlotRef CreateSlotAnimation(AnimationResource_00449870* resource, int index) {
    Entity* object = ((AnimationPool*)data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = 15;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object,index);
    return ((SlotLists*)data_00491c10)->RegisterPrimaryBack(object);
}
static __forceinline Entity* ResolveSlotAnimation(SlotRef* handle) {
    Entity* object = (Entity*)AnimationManager_Find_004491c0((AnimationLookupContext*)data_00491c10, *(AnimationScriptId*)handle);
    if (!object) handle->value = 0;
    return object;
}
#pragma code_seg(".text$00415b00_fn")
StageScoreDisplay::StageScoreDisplay(const void* description) {
    memset(this,0,sizeof(*this));
    first.Set(0);
    second.Set(0);
    field58 = 0;
    third.Set(0);
    definition = description;
    first_animation = CreateSlotAnimation(data_004776e0->resource,0);
    second_animation = CreateSlotAnimation(data_004776e0->resource,1);
    EntityTail(ResolveSlotAnimation(&first_animation))->layer_3a0 = 16;
    EntityTail(ResolveSlotAnimation(&first_animation))->layer_3a1 = 16;
    EntityTail(ResolveSlotAnimation(&second_animation))->layer_3a0 = 16;
    EntityTail(ResolveSlotAnimation(&second_animation))->layer_3a1 = 16;
    radius = SlotVector(8.0f,0.0f,0.0f);
    field80 = 0;
    color_a = 0xF8F08F;
    color_b = 0x8088FF;
    field84 = 0;
    region = SlotVector(24.0f,0.0f,0.0f);
    StageCollisionRecord* record = data_004776f0->records;
    for (int remaining=2000; remaining; --remaining,++record)
        if (record->state != 0 && record->state != 3) record->Activate();
    for (SlotEffect* node = g_laser_manager->first; node;) {
        SlotEffect* next = node->next;
        if (node->kind != 1) {
            node->Release(0);
        }
        node = next;
    }
    SweepDeaths(data_00477704);
}
#pragma code_seg()
