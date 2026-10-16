// 0x00441FE0: store a value into the +0x28 field and return that value.
// Native LTCG reproduces the private ABI seen in retail: the value arrives
// in EAX while the object arrives in ECX.
struct ObjectAccessor_00441fe0 {
    unsigned char pad_000[0x28];
    int field_028;
    __declspec(noinline) int StoreValue(int value);
};
typedef char ObjectAccessor_00441fe0_size_must_fit[sizeof(ObjectAccessor_00441fe0) == 0x2c ? 1 : -1];

#pragma code_seg(".text$01accessor00441fe0")
int ObjectAccessor_00441fe0::StoreValue(int value) {
    field_028 = value;
    return value;
}
#pragma code_seg()
