// 0x0040CC20: address of the sub-object at +0x13C0.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040cc20 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cc20::Offset() const {
    return (int)this + 0x13C0;
}
#pragma code_seg()
