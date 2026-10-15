// 0x00449530: find the node named by this object's first field, set flag bit 1
// and clear flag bit 17 on it, and do the same to every node in its child chain
// when it has no children of its own.
extern "C" void* g_sprt_ctrl;

struct AnimationNode_00449530 {
    AnimationNode_00449530* field_000;   // +0x000
    AnimationNode_00449530* field_004;   // +0x004
    unsigned char pad_008[0x0C];
    AnimationNode_00449530* field_014;   // +0x014
    AnimationNode_00449530* field_018;   // +0x018
    unsigned char pad_01c[0x340];
    unsigned int flags_35c;              // +0x35C
    __declspec(noinline) void Begin();
};

extern "C" AnimationNode_00449530* __fastcall AnimationManager_Find(
    void* value, void* manager, int unused);

#pragma code_seg(".text$01accessor")
void AnimationNode_00449530::Begin() {
    AnimationNode_00449530* node =
        AnimationManager_Find(field_000, g_sprt_ctrl, (int)field_000);
    if (node == 0) {
        return;
    }
    node->flags_35c = (node->flags_35c & ~0x20000u) | 2u;
    if (node->field_018 != 0) {
        return;
    }
    for (AnimationNode_00449530* child = node->field_014; child != 0; child = child->field_004) {
        child->field_000->flags_35c |= 2u;
        child->field_000->flags_35c &= ~0x20000u;
    }
}
#pragma code_seg()
