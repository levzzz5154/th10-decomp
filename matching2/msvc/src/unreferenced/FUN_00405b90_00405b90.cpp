// 0x00405B90..0x00405B94: signed 16-bit field accessor.
// Native LTCG supplies the object pointer in EAX.
struct ShortAccessor_00405b90 {
    unsigned char pad_000[8];
    short value;

    __declspec(noinline) short Load() const;
};

#pragma code_seg(".text$01target")
short ShortAccessor_00405b90::Load() const {
    return value;
}
#pragma code_seg()
