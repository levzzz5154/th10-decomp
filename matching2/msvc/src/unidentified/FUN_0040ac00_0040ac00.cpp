// 0x0040AC00..0x0040AC02: load the object's first field.
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster (layout/ltcg/accessor_load_field.json).

struct Object0040ac00 {
    int field_000;

    __declspec(noinline) int Load() const;
};

#pragma code_seg(".text$01accessor")
int Object0040ac00::Load() const {
    return field_000;
}
#pragma code_seg()
