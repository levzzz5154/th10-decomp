#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

// Full primary-back list registration corresponding to 0x004489D0. The
// returned four-byte reference has a genuine compiler-generated return home.
struct DispatcherPrimaryLists {
    unsigned char reserved_000[0x72DAD4];
    AnimationManagerNodeOpen* primary_head;
    AnimationManagerNodeOpen* primary_tail;
    unsigned char reserved_72dadc[0x732454 - 0x72DADC];
    int next_id;
    __declspec(noinline) DispatcherRef RegisterPrimaryBack(Entity* object);
};
typedef char DispatcherPrimaryHeadOffset[
    offsetof(DispatcherPrimaryLists, primary_head)==0x72DAD4?1:-1];
typedef char DispatcherPrimaryIdOffset[
    offsetof(DispatcherPrimaryLists, next_id)==0x732454?1:-1];

#pragma code_seg(".text$004489d0_fn")
DispatcherRef DispatcherPrimaryLists::RegisterPrimaryBack(Entity* object) {
    AnimationManagerNodeOpen* node = reinterpret_cast<AnimationManagerNodeOpen*>(
        &object->manager_node_animation);
    node->animation = object;
    node->next = 0;
    node->previous = 0;
    if (!primary_head)
        primary_head = node;
    else {
        AnimationManagerNodeOpen* tail = primary_tail;
        AnimationManagerNodeOpen* next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    primary_tail = node;
    if (++next_id == 0)
        ++next_id;
    object->animation_handle = next_id;
    return DispatcherRef(next_id);
}
#pragma code_seg()

// Full 0x00448D00 constructor path, with the actual three source inputs. The
// allocation, resource initialization and register bodies are complete graph
// dependencies; no explicit fabricated output parameter substitutes for sret.
#pragma code_seg(".text$00448d00_fn")
DispatcherRef __stdcall DispatcherCreateAnimation(
        AnimationResource_00449870* resource, int script_index, int render_bucket) {
    Entity* object = reinterpret_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = render_bucket;
    object->flags_35C = flags | 0x40000000;
    resource->InitializeObject(object, script_index);
    return reinterpret_cast<DispatcherPrimaryLists*>(data_00491c10)->RegisterPrimaryBack(object);
}
#pragma code_seg()

struct DispatcherFlagObject {
    unsigned char reserved_000[0x14];
    struct DispatcherFlagLink* children;
    int children_flagged;
    unsigned char reserved_01c[0x35C - 0x1C];
    unsigned flags;
};
struct DispatcherFlagLink {
    DispatcherFlagObject* object;
    DispatcherFlagLink* next;
};
typedef char DispatcherFlagOffset[
    offsetof(DispatcherFlagObject, flags)==0x35C?1:-1];

#pragma code_seg(".text$004492a0_fn")
void* __fastcall DispatcherRemoveAnimation(
        AnimationLookupContext* context, AnimationScriptId id) {
    DispatcherFlagObject* object = reinterpret_cast<DispatcherFlagObject*>(
        AnimationManager_Find_004491c0(context, id));
    if (object) {
        object->flags |= 0x04000000;
        if (!object->children_flagged) {
            DispatcherFlagLink* child = object->children;
            for (; child; child = child->next)
                child->object->flags |= 0x04000000;
            return child;
        }
    }
    return object;
}
#pragma code_seg()

struct DispatcherPositionObject {
    unsigned char reserved_000[0x14];
    struct DispatcherPositionLink* children;
    int children_flagged;
    unsigned char reserved_01c[0x340 - 0x1C];
    DispatcherVec3 position;
};
struct DispatcherPositionLink {
    DispatcherPositionObject* object;
    DispatcherPositionLink* next;
};
typedef char DispatcherPositionOffset[
    offsetof(DispatcherPositionObject, position)==0x340?1:-1];

#pragma code_seg(".text$004492f0_fn")
void DispatcherSetPosition(const DispatcherVec3* position,
        AnimationLookupContext* context, AnimationScriptId id) {
    DispatcherPositionObject* object = reinterpret_cast<DispatcherPositionObject*>(
        AnimationManager_Find_004491c0(context, id));
    if (object) {
        object->position = *position;
        if (!object->children_flagged)
            for (DispatcherPositionLink* child = object->children;
                 child; child = child->next)
                child->object->position = *position;
    }
}
#pragma code_seg()

