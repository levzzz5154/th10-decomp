// 0x0040CE40..0x0040CE49: load the nested object value.
//
// The native-LTCG caller supplies the private object pointer in EAX.  The
// declaration remains ordinary C++ while the cluster preserves that ABI.
struct H3301Nested_0040ce40 {
    unsigned char pad_000[0x78];
    int value_078;
};

struct H3301Outer_0040ce40 {
    unsigned char pad_000[0x9EB8];
    H3301Nested_0040ce40* nested_9EB8;
    __declspec(noinline) int GetValue() const;
};

#pragma code_seg(".text$01target")
int H3301Outer_0040ce40::GetValue() const {
    return nested_9EB8->value_078;
}
#pragma code_seg()
