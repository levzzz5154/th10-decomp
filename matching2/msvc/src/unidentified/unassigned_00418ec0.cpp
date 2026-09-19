// 0x00418EC0: set bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_00418ec0 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_00418ec0 {
    unsigned char pad_000[0x08];
    Flagged_00418ec0* first;
    Flagged_00418ec0* second;
};

void __declspec(noinline) SetFlags_00418ec0(ObjectAccessor_00418ec0* object);
#pragma code_seg(".text$01accessor")
void SetFlags_00418ec0(ObjectAccessor_00418ec0* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
