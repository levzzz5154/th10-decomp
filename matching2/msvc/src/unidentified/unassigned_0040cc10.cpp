// 0x0040CC10: return the address of the sub-object at +0x2C.
//
// The object pointer arrives in EAX, a convention no C++ declaration names, so
// this body is compiled as a single-function native-LTCG cluster.
struct ObjectAccessor_0040cc10 {
    __declspec(noinline) int Offset();
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040cc10::Offset() {
    return (int)this + 0x2C;
}
#pragma code_seg()
