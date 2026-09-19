// 0x004054A0: address of the sub-object at +0x3C0.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_004054a0 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_004054a0::Offset() const {
    return (int)this + 0x3C0;
}
#pragma code_seg()
