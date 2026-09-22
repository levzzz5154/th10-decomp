// 0x00418B60: store a short at the object halfword field +0x8.
// Native LTCG selects the observed object/value register convention.
struct H3701B60 {
    __declspec(noinline) void Store(short value);
};

#pragma code_seg(".text$01f")
void H3701B60::Store(short value) {
    *(short*)((char*)this + 8) = value;
}
#pragma code_seg()
