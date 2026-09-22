// 0x004087D0..0x004087D7: 16-bit field setter.
// Native LTCG assigns the object to EAX and the unsigned-short value to ECX.
struct H3401ShortField_004087d0 {
    unsigned char pad_000[0x304];
    unsigned short value_304;
    __declspec(noinline) void Set(unsigned short value);
};

#pragma code_seg(".text$01target")
void H3401ShortField_004087d0::Set(unsigned short value) {
    value_304 = value;
}
#pragma code_seg()
