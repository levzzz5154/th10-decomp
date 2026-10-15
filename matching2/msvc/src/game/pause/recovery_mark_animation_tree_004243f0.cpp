// 0x004243F0..0x00424430: set the stop frame of the animation a handle names,
// and of its children unless they were already flagged, to 6.  The same body
// as 0x00449470 with the frame fixed; compiled in that native-LTCG cluster so
// the handle arrives in EAX and the lookup keeps its private entry.
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

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* data_00491c10;

struct AnimationHandle_004243f0 {
    unsigned int value;
    __declspec(noinline) void StopAtFrame6();
};

#pragma code_seg(".text$45timedzb")
void AnimationHandle_004243f0::StopAtFrame6() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = 6;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 6;
        }
    }
}
#pragma code_seg()
