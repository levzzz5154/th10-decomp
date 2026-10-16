// 0x0040C4D0 - set the stop frame of the animation object registered under an
// animation handle to 3, and of that object's not-yet-flagged children.
// The same model as 0x0040C480; only the frame constant differs.

struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationTreeNode {
    AnimationTreeNode* object;              // +0x000
    AnimationTreeNode* next;                // +0x004
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;            // +0x014
    int children_flagged;                   // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;              // +0x304
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

struct AnimationHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

extern "C" AnimationLookupContext* g_sprt_ctrl;

#pragma code_seg(".text$30stop3")
void AnimationHandle::StopAtFrame3() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->Find(g_sprt_ctrl, id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 3;
        }
    }
}
#pragma code_seg()
