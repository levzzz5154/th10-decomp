// 0x0040B520: address of the sub-object at +0x1D86C.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040b520 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040b520::Offset() const {
    return (int)this + 0x1D86C;
}
#pragma code_seg()
