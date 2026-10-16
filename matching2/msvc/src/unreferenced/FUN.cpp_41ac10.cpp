// 0x0041AC10: store a value into the +0x38 field and return that value.
// Native LTCG reproduces the private ABI seen in retail: the value arrives
// in EAX while the object arrives in ECX.
struct ObjectAccessor_0041ac10 {
    unsigned char pad_000[0x38];
    int field_038;
    __declspec(noinline) int StoreValue(int value);
};
typedef char ObjectAccessor_0041ac10_size_must_fit[sizeof(ObjectAccessor_0041ac10) == 0x3c ? 1 : -1];

#pragma code_seg(".text$01accessor0041ac10")
int ObjectAccessor_0041ac10::StoreValue(int value) {
    field_038 = value;
    return value;
}
#pragma code_seg()
