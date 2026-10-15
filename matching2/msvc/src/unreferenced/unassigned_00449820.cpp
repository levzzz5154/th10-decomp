// 0x00449820..0x00449859: look up the animation a handle names and return its
// child whose script id matches.  A handle whose animation is gone is cleared.
// Compiled in the 0x004491C0 native-LTCG cluster so the lookup keeps its
// private entry.
struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationChild_00449820 {
    unsigned char reserved_000[0x38A];
    short script_id;                        // +0x38A
};

struct AnimationChildLink_00449820 {
    AnimationChild_00449820* object;
    AnimationChildLink_00449820* next;
};

struct AnimationNode_00449820 {
    unsigned char reserved_000[0x10];
    AnimationChildLink_00449820 children;   // +0x010
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* data_00491c10;

struct AnimationHandle_00449820 {
    AnimationScriptId id;
    __declspec(noinline) AnimationChild_00449820* FindChild(int script_id);
};

#pragma code_seg(".text$85child")
AnimationChild_00449820* AnimationHandle_00449820::FindChild(int script_id) {
    AnimationNode_00449820* node = reinterpret_cast<AnimationNode_00449820*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node == 0)
        id.value = 0;
    for (AnimationChildLink_00449820* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object;
    return 0;
}
#pragma code_seg()
