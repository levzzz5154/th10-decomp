// 0x00408AC0: raise bit 1 of the flags word of the +0x8 and +0xC sub-objects and
// of the object named by the +0x37AC pointer.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct SetTarget_00408ac0 {
    unsigned char pad_000[4];
    unsigned int flags;                       // +0x4
};

struct ObjectAccessor_00408ac0 {
    unsigned char pad_000[8];
    SetTarget_00408ac0* first;                // +0x8
    SetTarget_00408ac0* second;               // +0xC
    unsigned char pad_010[0x37AC - 0x10];
    SetTarget_00408ac0* third;                // +0x37AC
    __declspec(noinline) void Set();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00408ac0::Set() {
    if (first) first->flags |= 2u;
    if (second) second->flags |= 2u;
    third->flags |= 2u;
}
#pragma code_seg()
