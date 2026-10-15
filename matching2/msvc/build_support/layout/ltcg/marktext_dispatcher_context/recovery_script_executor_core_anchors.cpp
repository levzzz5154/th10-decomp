#include "../../../include/contexts/game/marktext_dispatcher_context/recovery_script_executor_0040bd80.hpp"
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
void* __fastcall RecoveryLookup_0040bd80::Find(RecoveryLookupContext_0040bd80* context, RecoveryScriptId_0040bd80 id) {
    if (!id.value)
        return 0;
    for (RecoveryLookupNode_0040bd80* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    for (RecoveryLookupNode_0040bd80* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<int*>(node->object) == id.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$004492a0_fn")
void* __fastcall RecoveryLookup_0040bd80::SetFlag(RecoveryLookupContext_0040bd80* context, int id) {
    RecoveryScriptId_0040bd80 script_id = { id };
    RecoveryLookupNode_0040bd80* node = static_cast<RecoveryLookupNode_0040bd80*>(Find(context, script_id));
    if (node) {
        node->flags |= 0x04000000u;
        if (!node->children_flagged)
            for (node = node->children; node != 0; node = node->next)
                node->object->flags |= 0x04000000u;
    }
    return node;
}
#pragma code_seg(".text$00449450_fn")
void* __cdecl RecoveryLookup_0040bd80::Validate(RecoveryHandle_0040bd80* handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle->value) };
    void* object = Find(reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id);
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
void RecoveryHandle_0040bd80::StopAtFrame2() {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(value) };
    RecoveryStopNode_0040bd80* node = static_cast<RecoveryStopNode_0040bd80*>(reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 2;
        if (!node->children_flagged)
            for (RecoveryStopNode_0040bd80* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 2;
    }
}
#pragma code_seg(".text$0040c4d0_fn")
void RecoveryHandle_0040bd80::StopAtFrame3() {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(value) };
    RecoveryStopNode_0040bd80* node = static_cast<RecoveryStopNode_0040bd80*>(reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged)
            for (RecoveryStopNode_0040bd80* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 3;
    }
}
#pragma code_seg(".text$00449630_fn")
void RecoveryHandle_0040bd80::MarkForRemoval() {
    reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->SetFlag(reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), static_cast<int>(value));
    value = 0;
}
#pragma code_seg()
