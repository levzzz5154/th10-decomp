// 0x0040C920: subtract the argument from the +0x0 field and return the new value.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040c920 {
    int field_0;                             // +0x0
    __declspec(noinline) int Accumulate(int value);
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c920::Accumulate(int value) {
    field_0 = field_0 - value;
    return field_0;
}
#pragma code_seg()
