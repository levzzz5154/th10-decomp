// 0x00434BF0..0x00434BFA: indexed nine-word value lookup.
//
// Native LTCG preserves the private object/index pair in ECX/EAX.
struct H3301Stride9_00434bf0 {
    unsigned char pad_000[0xB0];
    int values_0B0[9];
    __declspec(noinline) int GetValue(int index) const;
};

#pragma code_seg(".text$01target")
int H3301Stride9_00434bf0::GetValue(int index) const {
    return values_0B0[index * 9];
}
#pragma code_seg()
