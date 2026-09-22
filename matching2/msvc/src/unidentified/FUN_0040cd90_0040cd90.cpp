// 0x0040CD90: store an indexed integer in the object array at +0x10.
// Native LTCG selects the observed object/index/value register convention.
struct H3701CD90 {
    __declspec(noinline) void Store(int index, int value);
};

#pragma code_seg(".text$01f")
void H3701CD90::Store(int index, int value) {
    ((int*)this)[index + 4] = value;
}
#pragma code_seg()
