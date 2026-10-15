#include "../../../include/contexts/game/right_aligned_text_context/recovery_script_executor_0040bd80.hpp"
extern "C" void* g_sprt_ctrl;
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
#pragma code_seg(".text$00405410_fn")
void RecoveryTimer_0040bd80::Set(int value) {
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
void RecoveryTimer_0040bd80::Advance(float delta) {
    previous = current;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper)
        elapsed += delta;
    else
        elapsed += delta * *speed;
    current = int(elapsed);
}
#pragma code_seg(".text$004491c0_fn")
void* __fastcall RecoveryLookup::Find(RecoveryLookupContext* context, RecoveryScriptId id) {
    if (!id.value)
        return 0;
    for (RecoveryLookupNode* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (RecoveryLookupNode* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$004492a0_fn")
void* __fastcall RecoveryLookup::SetFlag(RecoveryLookupContext* context, int id) {
    RecoveryScriptId script_id = { id };
    RecoveryLookupNode* node = static_cast<RecoveryLookupNode*>(Find(context, script_id));
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg(".text$00449450_fn")
void* __cdecl RecoveryLookup::Validate(RecoveryHandle* handle) {
    RecoveryScriptId id = { static_cast<int>(handle->value) };
    void* object = Find(reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id);
    if (object == 0)
        handle->value = 0;
    return object;
}
struct RecoveryStopNode_0040bd80 {
    RecoveryStopNode_0040bd80* object;
    RecoveryStopNode_0040bd80* next;
    unsigned char reserved_008[0x0C];
    RecoveryStopNode_0040bd80* children;
    int children_flagged;
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;
};
#pragma code_seg(".text$0040c480_fn")
void RecoveryHandle::StopAtFrame2() {
    RecoveryScriptId id = { static_cast<int>(value) };
    RecoveryStopNode_0040bd80* node = static_cast<RecoveryStopNode_0040bd80*>(reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 2;
        if (!node->children_flagged)
            for (RecoveryStopNode_0040bd80* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 2;
    }
}
#pragma code_seg(".text$0040c4d0_fn")
void RecoveryHandle::StopAtFrame3() {
    RecoveryScriptId id = { static_cast<int>(value) };
    RecoveryStopNode_0040bd80* node = static_cast<RecoveryStopNode_0040bd80*>(reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged)
            for (RecoveryStopNode_0040bd80* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg(".text$00449630_fn")
void RecoveryHandle::MarkForRemoval() {
    reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->SetFlag(reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), static_cast<int>(value));
    value = 0;
}
#pragma code_seg()
