// 0x00408820: address of the sub-object at +0x1068.
//
// The object pointer arrives in EAX, a convention no C++ declaration
// names, so the body is compiled as a single-function native-LTCG cluster
// whose synthetic caller walks an array of objects.
struct ObjectAccessor_00408820 {
    __declspec(noinline) int Offset() const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_00408820::Offset() const {
    return (int)this + 0x1068;
}
#pragma code_seg()
