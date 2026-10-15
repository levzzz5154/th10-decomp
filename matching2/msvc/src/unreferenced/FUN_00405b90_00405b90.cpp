// 0x00405B90..0x00405B94: signed 16-bit field accessor.
// Native LTCG supplies the object pointer in EAX.
struct ShortAccessor {
    unsigned char pad_000[8];
    short value;

    __declspec(noinline) short Load() const;
};

#pragma code_seg(".text$01target")
short ShortAccessor::Load() const {
    return value;
}
#pragma code_seg()
