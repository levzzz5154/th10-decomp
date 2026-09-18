// 0x00409E50 - resolve the animation object behind an animation handle and set
// its sprite word to 1, propagating that value to the object's direct children
// unless the object is already flagged as having processed them.
//
// The handle is the receiver and the only input: retail's callers put its
// address in EAX and nothing else, and the animation lookup never reads its own
// receiver, so the whole-program pass leaves EAX holding the dereferenced
// pointer and hands the lookup's id back on the stack.  Both are conventions
// only a native-LTCG cluster reaches; this unit is co-compiled with the
// StopAtFrame pair that owns 0x004491C0 (layout/ltcg/stop_at_frame_pair_0040c480.json).

struct AnimationLookupContext;

// The script id is a four-byte record so the lookup reads it from its stack
// slot; see the note in animation_manager_find_004491c0.cpp.
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

struct AnimationHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$05propagate")
void AnimationHandle::StopAtFrame1() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = 1;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}
#pragma code_seg()
