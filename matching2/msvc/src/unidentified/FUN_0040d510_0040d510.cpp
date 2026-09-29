// 0x0040D510: set bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_0040d510 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_0040d510 {
    unsigned char pad_000[0x08];
    Flagged_0040d510* first;
    Flagged_0040d510* second;
};

void __declspec(noinline) SetFlags_0040d510(ObjectAccessor_0040d510* object);
#pragma code_seg(".text$01accessor")
void SetFlags_0040d510(ObjectAccessor_0040d510* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
