// Child lookup over the intrusive list embedded at +0x10 of the animation
// object. Native LTCG selects the private EAX receiver and ECX id convention.
struct AnimationObject17 {
    unsigned char reserved_000[0x38a];
    short script_index;
};

struct AnimationListNode2 {
    AnimationObject17* object;
    AnimationListNode2* next;
};

struct AnimationManager16 {
    unsigned char reserved_000[0x10];
    __declspec(noinline) AnimationObject17* FindChildByScriptIndex(int id);
};

#pragma code_seg(".text$05findchild")
AnimationObject17*
AnimationManager16::FindChildByScriptIndex(int id) {
    for (AnimationListNode2* node =
             (AnimationListNode2*)((char*)this + 0x10);
         node != 0; node = node->next) {
        if (node->object->script_index == id)
            return node->object;
    }
    return 0;
}
#pragma code_seg()
