// 0x0040AE00: clear bit 1 of the flags word of both +0x8 and +0xC sub-objects.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// the body is compiled as a single-function native-LTCG cluster.
struct ClearTarget {
    unsigned char pad_000[4];
    unsigned int flags;                       // +0x4
};

struct ObjectAccessor_0040ae00 {
    unsigned char pad_000[8];
    ClearTarget* first;              // +0x8
    ClearTarget* second;             // +0xC
    __declspec(noinline) void Clear();
};

#pragma code_seg(".text$01accessor")
void ObjectAccessor_0040ae00::Clear() {
    if (first) first->flags &= ~2u;
    if (second) second->flags &= ~2u;
}
#pragma code_seg()
