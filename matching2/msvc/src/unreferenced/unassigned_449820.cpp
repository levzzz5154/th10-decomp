// 0x00449820..0x00449859: look up the animation a handle names and return its
// child whose script id matches.  A handle whose animation is gone is cleared.
// Compiled in the 0x004491C0 native-LTCG cluster so the lookup keeps its
// private entry.
struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationChild2 {
    unsigned char reserved_000[0x38A];
    short script_id;                        // +0x38A
};

struct AnimationChildLink2 {
    AnimationChild2* object;
    AnimationChildLink2* next;
};

struct AnimationNode13 {
    unsigned char reserved_000[0x10];
    AnimationChildLink2 children;   // +0x010
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationHandle16 {
    AnimationScriptId id;
    __declspec(noinline) AnimationChild2* FindChild(int script_id);
};

#pragma code_seg(".text$85child")
AnimationChild2* AnimationHandle16::FindChild(int script_id) {
    AnimationNode13* node = reinterpret_cast<AnimationNode13*>(
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->Find(g_sprt_ctrl, id));
    if (node == 0)
        id.value = 0;
    for (AnimationChildLink2* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object;
    return 0;
}
#pragma code_seg()
