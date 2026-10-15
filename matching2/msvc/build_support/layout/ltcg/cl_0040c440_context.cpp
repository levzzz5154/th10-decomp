// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0040c440.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_0040c440* handle) {
    unsigned int id = handle->id;
    AnimationNode_0040c440* node = (AnimationNode_0040c440*)find_opaque_004491c0(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode_0040c440* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_0040c440(Entity_0040c440** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandleAndClear();
    }
    return 0;
}
#pragma code_seg()
