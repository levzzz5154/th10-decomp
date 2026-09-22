// 0x0042A9D0: load the signed 16-bit value from the object in EAX.
struct WordLoad_0042a9d0 {
    unsigned short value;
    __declspec(noinline) short Load();
};
typedef char WordLoad_0042a9d0_size_must_fit[sizeof(WordLoad_0042a9d0) == 2 ? 1 : -1];

#pragma code_seg(".text$01load0042a9d0")
short WordLoad_0042a9d0::Load() {
    return (short)value;
}
#pragma code_seg()
