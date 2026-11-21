// 0x0040C950: store an indexed integer in the private object array.
// Native LTCG selects the observed object/index/value register convention.
struct H3701C950 {
    __declspec(noinline) void Store(int index, int value);
};

#pragma code_seg(".text$01f")
void H3701C950::Store(int index, int value) {
    ((int*)this)[index] = value;
}
#pragma code_seg()
