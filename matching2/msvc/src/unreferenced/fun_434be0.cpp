// 0x00434BE0..0x00434BE7: indexed resource-slot lookup.
// Native LTCG preserves the object/index pair in EAX/ECX.
struct H3401Slots {
    unsigned char pad_000[0x3AD06C];
    int slots_3ad06c[0x21];
    __declspec(noinline) int Get(int index) const;
};

#pragma code_seg(".text$01target")
int H3401Slots::Get(int index) const {
    return slots_3ad06c[index];
}
#pragma code_seg()
