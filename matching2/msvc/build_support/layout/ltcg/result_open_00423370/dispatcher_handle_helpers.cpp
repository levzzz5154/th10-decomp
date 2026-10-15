// Complete ordinary C++ models for the genuine animation-handle calls made
// by result dispatcher 00415E90. Native private register choices are derived
// by the caller graph; these methods have only their actual source inputs.
#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

#pragma code_seg(".text$00405410_fn")
void DispatcherWaitTimer::SetSchedulerValue(int value) {
    if (!(flags & 1u)) {
        current = 0;
        previous = -999999;
        elapsed = 0.0f;
        speed = &g_game_speed;
        flags |= 1u;
    }
    current = value;
    previous = value - 1;
    elapsed = static_cast<float>(value);
}
#pragma code_seg()

// Rank records have a complete 48-byte stride. The dispatcher needs only the
// music-slot prefix view; both types address the same selected record.
struct DispatcherRankEntry {
    int values[12];
};
extern "C" DispatcherRankEntry g_stage_routes[];
extern "C" DispatcherMusicRecord* g_stage_route_current;
typedef char DispatcherRankEntrySize[sizeof(DispatcherRankEntry) == 0x30 ? 1 : -1];

#pragma code_seg(".text$004175e0_fn")
void DispatcherRankState::AdvanceLevel() {
    if (level < 7)
        ++level;
    g_stage_route_current = reinterpret_cast<DispatcherMusicRecord*>(
        &g_stage_routes[level]);
}
#pragma code_seg()

struct DispatcherTreeObject {
    unsigned char reserved_000[0x14];
    struct DispatcherTreeLink* children;
    int children_flagged;
    unsigned char reserved_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};
struct DispatcherTreeLink {
    DispatcherTreeObject* object;
    DispatcherTreeLink* next;
};
typedef char DispatcherTreeChildrenOffset[
    offsetof(DispatcherTreeObject, children) == 0x14 ? 1 : -1];
typedef char DispatcherTreeStopOffset[
    offsetof(DispatcherTreeObject, stop_frame) == 0x304 ? 1 : -1];

#pragma code_seg(".text$00409e50_fn")
void DispatcherHandle::StopAtFrame1() {
    DispatcherTreeObject* object = reinterpret_cast<DispatcherTreeObject*>(
        DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = 1;
        if (!object->children_flagged)
            for (DispatcherTreeLink* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
    }
}
#pragma code_seg()

#pragma code_seg(".text$0040c480_fn")
void DispatcherHandle::StopAtFrame2() {
    DispatcherTreeObject* object = reinterpret_cast<DispatcherTreeObject*>(
        DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = 2;
        if (!object->children_flagged)
            for (DispatcherTreeLink* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 2;
    }
}
#pragma code_seg()

#pragma code_seg(".text$0040c4d0_fn")
void DispatcherHandle::StopAtFrame3() {
    DispatcherTreeObject* object = reinterpret_cast<DispatcherTreeObject*>(
        DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = 3;
        if (!object->children_flagged)
            for (DispatcherTreeLink* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg()

#pragma code_seg(".text$00449470_fn")
void DispatcherHandle::SetStopFrame(short frame) {
    DispatcherTreeObject* object = reinterpret_cast<DispatcherTreeObject*>(
        DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0) {
        object->stop_frame = frame;
        if (!object->children_flagged)
            for (DispatcherTreeLink* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
    }
}
#pragma code_seg()

struct DispatcherChildObject {
    int value;
    unsigned char reserved_004[0x38A - 4];
    short script_id;
};
struct DispatcherChildLink {
    DispatcherChildObject* object;
    DispatcherChildLink* next;
};
struct DispatcherParentObject {
    unsigned char reserved_000[0x10];
    DispatcherChildLink children;
};
typedef char DispatcherChildScriptOffset[
    offsetof(DispatcherChildObject, script_id) == 0x38A ? 1 : -1];
typedef char DispatcherChildHeadOffset[
    offsetof(DispatcherParentObject, children) == 0x10 ? 1 : -1];

#pragma code_seg(".text$004497d0_fn")
DispatcherRef DispatcherHandle::FindChildRef(int script_id) {
    DispatcherParentObject* object = reinterpret_cast<DispatcherParentObject*>(
        DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object == 0)
        id.value = 0;
    // Retail forms this embedded list head even when the lookup failed; keep
    // that behavior rather than introduce a different missing-parent guard.
    for (DispatcherChildLink* child = &object->children;
         child != 0; child = child->next)
        if (child->object->script_id == script_id)
            return DispatcherRef(child->object->value);
    return DispatcherRef(0);
}
#pragma code_seg()

#pragma code_seg(".text$00449670_fn")
void DispatcherRef::SelectCurrentSprite(int index) {
    AnimationScriptId id(value);
    AnimationObject_0043e5a0* object =
        reinterpret_cast<AnimationObject_0043e5a0*>(
            DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0)
        object->resource->ConfigureObject(object, index);
}
#pragma code_seg()

#pragma code_seg(".text$004496a0_fn")
void DispatcherRef::SelectResourceSprite(
        AnimationBank* resource, int index) {
    AnimationScriptId id(value);
    AnimationObject_0043e5a0* object =
        reinterpret_cast<AnimationObject_0043e5a0*>(
            DispatcherFindAnimation(
            reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl), id));
    if (object != 0)
        reinterpret_cast<Resource_0043e5a0*>(resource)->ConfigureObject(object, index);
}
#pragma code_seg()
