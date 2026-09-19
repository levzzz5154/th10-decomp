// 0x0040C530: mask the word at +0x0.
//
// The object pointer arrives in EAX and the mask in ECX, a register pair no
// C++ declaration names, so the body is compiled as a single-function
// native-LTCG cluster whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040c530 {
    unsigned short field_000;               // +0x0
    __declspec(noinline) int LoadMasked(int mask) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040c530::LoadMasked(int mask) const {
    return (int)field_000 & mask;
}
#pragma code_seg()
