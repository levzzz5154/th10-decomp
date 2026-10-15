// 0x00418A70: clear bit 1 of the two owned flag words
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct Flagged_00418a70 {
    unsigned char pad_000[0x04];
    unsigned int flags;
};

struct ObjectAccessor_00418a70 {
    unsigned char pad_000[0x0C];
    Flagged_00418a70* low;
    unsigned char pad_010[0x1CC - 0x10];
    Flagged_00418a70* high;
};

void __declspec(noinline) ClearFlags(ObjectAccessor_00418a70* object);
#pragma code_seg(".text$01accessor")
void ClearFlags(ObjectAccessor_00418a70* object) {
    if (object->high) {
        object->high->flags &= ~2u;
    }
    if (object->low) {
        object->low->flags &= ~2u;
    }
}
#pragma code_seg()
