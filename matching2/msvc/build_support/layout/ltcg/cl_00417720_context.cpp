// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00417720.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_00417720* handle) {
    unsigned int id = handle->id;
    AnimationNode_00417720* node = (AnimationNode_00417720*)find_opaque_004491c0(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode_00417720* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_00417720(Entity_00417720** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandle();
    }
    return 0;
}
#pragma code_seg()
