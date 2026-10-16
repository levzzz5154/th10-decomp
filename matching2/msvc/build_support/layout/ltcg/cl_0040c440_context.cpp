// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_40c440.cpp"

#pragma code_seg(".text$01anchor")
__declspec(noinline) void StopHandleAnchor2(AnimationHandle4* handle) {
    unsigned int id = handle->id;
    AnimationNode3* node = (AnimationNode3*)find_opaque(id);
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationNode3* child = node->children; child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StopContext_0040c440(Entity2** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->StopHandleAndClear();
    }
    return 0;
}
#pragma code_seg()
