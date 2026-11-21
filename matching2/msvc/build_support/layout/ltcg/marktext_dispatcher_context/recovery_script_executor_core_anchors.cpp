#include "th10/game/ending_script/script_executor.hpp"
extern "C" void* g_sprt_ctrl;
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
#pragma code_seg(".text$00405410_fn")
void GameFrameTimer::Set(int value) {
    if (!(flags & 1u)) {
        current = 0;
        previous = static_cast<int>(0xFFF0BDC1u);
        elapsed = 0.0f;
        speed = reinterpret_cast<const float*>(0x00476F78u);
        flags |= 1u;
    }
    current = value;
    previous = value - 1;
    elapsed = static_cast<float>(value);
}
#pragma code_seg(".text$0044bf40_fn")
void GameFrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper)
        elapsed += delta;
    else
        elapsed += delta * *speed;
    current = int(elapsed);
}
#pragma code_seg(".text$004491c0_fn")
void* __fastcall AnmLookup::Find(AnmLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnmLookupNode* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (AnmLookupNode* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
// A cluster that places another body at these retail addresses parks these
// through TH10_LOOKUP_SETFLAG_SECTION and TH10_LOOKUP_VALIDATE_SECTION.
#ifndef TH10_LOOKUP_SETFLAG_SECTION
#define TH10_LOOKUP_SETFLAG_SECTION ".text$004492a0_fn"
#endif
#pragma code_seg(TH10_LOOKUP_SETFLAG_SECTION)
void* __fastcall AnmLookup::SetFlag(AnmLookupContext* context, int id) {
    AnimationScriptId script_id = { id };
    AnmLookupNode* node = static_cast<AnmLookupNode*>(Find(context, script_id));
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#ifndef TH10_LOOKUP_VALIDATE_SECTION
#define TH10_LOOKUP_VALIDATE_SECTION ".text$00449450_fn"
#endif
#pragma code_seg(TH10_LOOKUP_VALIDATE_SECTION)
void* __cdecl AnmLookup::Validate(AnmScriptHandle* handle) {
    AnimationScriptId id = { static_cast<int>(handle->value) };
    void* object = Find(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id);
    if (object == 0)
        handle->value = 0;
    return object;
}
struct EndingScriptStopNode {
    EndingScriptStopNode* object;
    EndingScriptStopNode* next;
    unsigned char reserved_008[0x0C];
    EndingScriptStopNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;
};
#pragma code_seg(".text$0040c480_fn")
void AnmScriptHandle::StopAtFrame2() {
    AnimationScriptId id = { static_cast<int>(value) };
    EndingScriptStopNode* node = static_cast<EndingScriptStopNode*>(reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 2;
        if (!node->children_flagged)
            for (EndingScriptStopNode* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 2;
    }
}
#pragma code_seg(".text$0040c4d0_fn")
void AnmScriptHandle::StopAtFrame3() {
    AnimationScriptId id = { static_cast<int>(value) };
    EndingScriptStopNode* node = static_cast<EndingScriptStopNode*>(reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged)
            for (EndingScriptStopNode* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg(".text$00449630_fn")
void AnmScriptHandle::MarkForRemoval() {
    reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->SetFlag(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), static_cast<int>(value));
    value = 0;
}
#pragma code_seg()
