#include "end.cpp"
#include "lookup.cpp"
// 0x00409E50
#pragma code_seg(".text$00409e50_fn")
void AnimationHandle::StopAtFrame1() {
    ResultAnimationId id;
    id.value = value;
    ResultAnimationEntry* node =
        static_cast<ResultAnimationEntry*>(ResultAnimation_Find(g_sprt_ctrl, id));
    if (node) {
        node->flags = 1;
        if (!node->children_flagged)
            for (ResultAnimationEntry* child = node->children; child; child = child->next)
                child->object->flags = 1;
    }
}

// 0x0043DC90
#define TH10_SOUND_QUEUE_SECTION ".text$0043dc90_fn"
#include "../../../../src/core/sound/sound_queue.cpp"

