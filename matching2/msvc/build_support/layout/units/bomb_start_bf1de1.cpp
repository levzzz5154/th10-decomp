#include "th10/source_views/bomb_start_bf1de1_0.hpp"
int* AnimationPrimaryLists::RegisterPrimaryBack(int* out, Entity* entity) {
    PrimaryListNode* node = reinterpret_cast<PrimaryListNode*>(&entity->manager_node_animation);
    node->owner = entity;
    node->next = 0;
    node->previous = 0;
    if (!head) head = node;
    else {
        PrimaryListNode* old = tail;
        if (old->next) {
            node->next = old->next;
            old->next->previous = node;
        }
        old->next = node;
        node->previous = old;
    }
    tail = node;
    ++serial;
    if (!serial) ++serial;
    entity->animation_handle = serial;
    *out = serial;
    return out;
}
#include "th10/source_views/bomb_start_bf1de1_1.hpp"
__declspec(noinline) int* __stdcall CreateScreenPositionedPrimary(
    AnimationResourceFile* resource, int* out, int index, const Vector3* position) {
    Entity* object = reinterpret_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags = object->flags_35C;
    object->render_bucket = 0;
    object->flags_35C = flags | 0x40000000;
    object->position.x = position->x + flt_224;
    object->position.y = position->y + flt_16;
    object->position.z = position->z;
    LoadScript2(resource, static_cast<AnimationObjectFile*>(object), index);
    reinterpret_cast<AnimationPrimaryLists*>(g_sprt_ctrl)->RegisterPrimaryBack(out, object);
    return out;
}
#include "th10/source_views/bomb_start_bf1de1_2.hpp"
#include "../../../src/game/bomb/bomb_start.cpp"

#pragma code_seg()
