// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_417720.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor2(AnimationHandle5* handle) {
    unsigned int id = handle->id;
    AnimationNode5* node = (AnimationNode5*)find_opaque(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode5* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_00417720(Entity3** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandle();
    }
    return 0;
}
#pragma code_seg()
