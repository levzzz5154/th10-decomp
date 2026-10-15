// 0x00412D50: store a value into the +0x38 field and return that value.
// Native LTCG reproduces the private ABI seen in retail: the value arrives
// in EAX while the object arrives in ECX.
struct StoreResult {
    unsigned char pad_000[0x38];
    int field_038;
    __declspec(noinline) int Store(int value);
};
typedef char StoreResult_00412d50_size_must_fit[sizeof(StoreResult) == 0x3c ? 1 : -1];

#pragma code_seg(".text$01store00412d50")
int StoreResult::Store(int value) {
    field_038 = value;
    return value;
}
#pragma code_seg()
