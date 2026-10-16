// 0x00422200: set bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged6 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_00422200 {
    unsigned char pad_000[0x08];
    Flagged6* first;
    Flagged6* second;
};

void __declspec(noinline) SetFlags3(ObjectAccessor_00422200* object);
#pragma code_seg(".text$01accessor")
void SetFlags3(ObjectAccessor_00422200* object) {
    if (object->first) {
        object->first->flags |= 2u;
    }
    if (object->second) {
        object->second->flags |= 2u;
    }
}
#pragma code_seg()
