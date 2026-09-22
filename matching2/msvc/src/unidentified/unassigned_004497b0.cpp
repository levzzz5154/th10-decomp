// Child lookup over the intrusive list embedded at +0x10 of the animation
// object. Native LTCG selects the private EAX receiver and ECX id convention.
struct AnimationObject_004497b0 {
    unsigned char reserved_000[0x38a];
    short script_index;
};

struct AnimationListNode_004497b0 {
    AnimationObject_004497b0* object;
    AnimationListNode_004497b0* next;
};

struct AnimationManager_004497b0 {
    unsigned char reserved_000[0x10];
    __declspec(noinline) AnimationObject_004497b0* FindChildByScriptIndex(int id);
};

#pragma code_seg(".text$05findchild")
AnimationObject_004497b0*
AnimationManager_004497b0::FindChildByScriptIndex(int id) {
    for (AnimationListNode_004497b0* node =
             (AnimationListNode_004497b0*)((char*)this + 0x10);
         node != 0; node = node->next) {
        if (node->object->script_index == id)
            return node->object;
    }
    return 0;
}
#pragma code_seg()
