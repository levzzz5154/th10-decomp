// 0x0040C470: return the field at +0x4 modulo the argument.
//
// The object pointer arrives in EAX, a convention no C++ declaration names,
// so the body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040c470 {
    unsigned char pad_000[0x4];
    int field_4;                             // +0x4
    __declspec(noinline) int Remainder(int divisor) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c470::Remainder(int divisor) const {
    return field_4 % divisor;
}
#pragma code_seg()
