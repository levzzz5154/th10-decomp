// 0x00449250..0x0044929B: set the stop frame and run the animation immediately.
// Children receive the same operation unless the parent marks them processed.
#include "th10/render/animation_stop_run.hpp"

#pragma code_seg(".text$65stoprun")
__declspec(noinline) void __fastcall AnimationManager_SetStopFrameAndRun(
        unsigned short frame, AnimationLookupContext* context, AnimationScriptId id) {
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<SprtCtrl*>(context)->Find(context, id));
    if (node != 0) {
        node->stop_frame = frame;
        RunAnimationVm(node);
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next) {
                child->object->stop_frame = frame;
                RunAnimationVm(child->object);
            }
        }
    }
}
#pragma code_seg()
