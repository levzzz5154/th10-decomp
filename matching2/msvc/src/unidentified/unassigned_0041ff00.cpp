// 0x0041FF00: mark the three owned slots with bit 1
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_0041ff00 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_0041ff00 {
    unsigned char pad_000[0x0C];
    Flagged_0041ff00* first;
    Flagged_0041ff00* second;
    unsigned char pad_014[0x89A8 - 0x14];
    Flagged_0041ff00* third;
};

void __declspec(noinline) Mark_0041ff00(ObjectAccessor_0041ff00* object);
#pragma code_seg(".text$01accessor")
void Mark_0041ff00(ObjectAccessor_0041ff00* object) {
    object->first->flags |= 2u;
    object->second->flags |= 2u;
    object->third->flags |= 2u;
}
#pragma code_seg()
