// 0x004497D0..0x00449815: look up the animation a handle names and return a
// reference to its child whose script id matches, or a null reference.  A
// handle whose animation is gone is cleared.  The by-value twin of 0x00449820:
// the reference comes back through a hidden pointer, which the native-LTCG
// link of the 0x004491C0 cluster passes in EDI.
struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationRef_004497d0 {
    int value;
    AnimationRef_004497d0(int value) : value(value) {}
};

struct AnimationChild_004497d0 {
    AnimationRef_004497d0 ref;              // +0x000
    unsigned char reserved_004[0x386];
    short script_id;                        // +0x38A
};

struct AnimationChildLink_004497d0 {
    AnimationChild_004497d0* object;
    AnimationChildLink_004497d0* next;
};

struct AnimationNode_004497d0 {
    unsigned char reserved_000[0x10];
    AnimationChildLink_004497d0 children;   // +0x010
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* data_00491c10;

struct AnimationHandle_004497d0 {
    AnimationScriptId id;
    __declspec(noinline) AnimationRef_004497d0 FindChildRef(int script_id);
};

#pragma code_seg(".text$84childref")
AnimationRef_004497d0 AnimationHandle_004497d0::FindChildRef(int script_id) {
    AnimationNode_004497d0* node = reinterpret_cast<AnimationNode_004497d0*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node == 0)
        id.value = 0;
    for (AnimationChildLink_004497d0* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object->ref;
    return AnimationRef_004497d0(0);
}
#pragma code_seg()
