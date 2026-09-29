// 0x00449210..0x00449245: look a script id up and set the stop frame of the
// animation it names, and of its children unless they were already flagged.
// The id-taking sibling of 0x00449470; compiled in the same native-LTCG
// cluster, whose pass keeps the lookup context in EDX and the frame in SI.
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

void __fastcall AnimationManager_SetStopFrame(unsigned short frame, AnimationLookupContext* context,
                                              AnimationScriptId id);

#pragma code_seg(".text$60layoutb")
__declspec(noinline) void __fastcall AnimationManager_SetStopFrame(
        unsigned short frame, AnimationLookupContext* context, AnimationScriptId id) {
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(context)->Find(context, id));
    if (node != 0) {
        node->stop_frame = frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}
#pragma code_seg()
