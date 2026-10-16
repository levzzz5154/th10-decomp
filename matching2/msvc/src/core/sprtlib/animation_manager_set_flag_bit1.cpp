// 0x00449590: find the node named by this object's first field, raise flag bit 1
// on it, and on every node in its child chain when it has no children of its own.
extern "C" void* g_sprt_ctrl;

struct AnimationNode10 {
    AnimationNode10* field_000;   // +0x000
    AnimationNode10* field_004;   // +0x004
    unsigned char pad_008[0x0C];
    AnimationNode10* field_014;   // +0x014
    AnimationNode10* field_018;   // +0x018
    unsigned char pad_01c[0x340];
    unsigned int flags_35c;              // +0x35C
    __declspec(noinline) void SetFlag();
};

extern "C" AnimationNode10* __fastcall AnimationManager_Find(
    void* value, void* manager, int unused);

#pragma code_seg(".text$01accessor")
void AnimationNode10::SetFlag() {
    AnimationNode10* node =
        AnimationManager_Find(field_000, g_sprt_ctrl, (int)field_000);
    if (node == 0) {
        return;
    }
    node->flags_35c |= 2;
    if (node->field_018 != 0) {
        return;
    }
    for (AnimationNode10* child = node->field_014; child != 0; child = child->field_004) {
        child->field_000->flags_35c |= 2;
    }
}
#pragma code_seg()
