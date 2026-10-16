// 0x004497D0..0x00449815: look up the animation a handle names and return a
// reference to its child whose script id matches, or a null reference.  A
// handle whose animation is gone is cleared.  The by-value twin of 0x00449820:
// the reference comes back through a hidden pointer, which the native-LTCG
// link of the 0x004491C0 cluster passes in EDI.
struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

struct AnimationRef2 {
    int value;
    AnimationRef2(int value) : value(value) {}
};

struct AnimationChild {
    AnimationRef2 ref;              // +0x000
    unsigned char reserved_004[0x386];
    short script_id;                        // +0x38A
};

struct AnimationChildLink {
    AnimationChild* object;
    AnimationChildLink* next;
};

struct AnimationNode12 {
    unsigned char reserved_000[0x10];
    AnimationChildLink children;   // +0x010
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationHandle15 {
    AnimationScriptId id;
    __declspec(noinline) AnimationRef2 FindChildRef(int script_id);
};

#pragma code_seg(".text$84childref")
AnimationRef2 AnimationHandle15::FindChildRef(int script_id) {
    AnimationNode12* node = reinterpret_cast<AnimationNode12*>(
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->Find(g_sprt_ctrl, id));
    if (node == 0)
        id.value = 0;
    for (AnimationChildLink* link = &node->children; link != 0; link = link->next)
        if (link->object->script_id == script_id)
            return link->object->ref;
    return AnimationRef2(0);
}
#pragma code_seg()
