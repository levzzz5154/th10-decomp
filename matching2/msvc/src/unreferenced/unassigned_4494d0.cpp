// 0x004494D0: look up the animation object named by field_000 and update
// bits in its +0x35C word.  When field_018 is zero, apply the same transition
// to the objects referenced by the +0x14 linked list.
//
// The field names and bit meanings remain deliberately numeric.  The retail
// entry receives this object in EAX; the LTCG context supplies that private
// receiver convention.  The retail body continues through the loop formerly
// split into the 0x00449510 assembly region.
extern "C" void* g_sprt_ctrl;

struct AnimationNode8;

struct AnimationObjectLink {
    AnimationNode8* object;       // +0x00
    AnimationObjectLink* next;   // +0x04
};

struct AnimationNode8 {
    void* field_000;                      // +0x00: value passed to Find
    unsigned char unknown_004[0x10];      // +0x04
    AnimationObjectLink* field_014;
    unsigned int field_018;
    unsigned char unknown_01c[0x340];
    unsigned int flags_35c;

    __declspec(noinline) void UpdateFlags();
};

extern "C" AnimationNode8* __fastcall AnimationManager_Find(
    void* value, void* manager, int unused);

#pragma code_seg(".text$01accessor")
void AnimationNode8::UpdateFlags() {
    AnimationNode8* node =
        AnimationManager_Find(field_000, g_sprt_ctrl, (int)field_000);
    if (node == 0) {
        return;
    }

    node->flags_35c = (node->flags_35c & ~2u) | 0x20000u;
    if (node->field_018 != 0) {
        return;
    }

    for (AnimationObjectLink* child = node->field_014;
         child != 0;
         child = child->next) {
        child->object->flags_35c &= ~2u;
        child->object->flags_35c |= 0x20000u;
    }
}
#pragma code_seg()
