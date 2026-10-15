// 0x00412E00: clear the object field at +0x34.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster
// (build_support/layout/ltcg/accessor_00412e00.json).
// The neighbour at 0x00412DF0 loads the same +0x34 word.

struct ObjectAccessor_00412e00 {
    unsigned char pad_000[0x34];
    int field_034;
    __declspec(noinline) void Clear();
};
typedef char ObjectAccessor_00412e00_size_must_fit[sizeof(ObjectAccessor_00412e00) == 0x38 ? 1 : -1];

#pragma code_seg(".text$01clear")
void ObjectAccessor_00412e00::Clear() {
    field_034 = 0;
}
#pragma code_seg()
