// 0x0040ACC0: mask the +0x8 word.
//
// The object pointer arrives in EAX and the mask in ECX, a register pair no
// C++ declaration names, so the body is compiled as a single-function
// native-LTCG cluster whose synthetic caller walks an array of objects.
struct ObjectAccessor_0040acc0 {
    unsigned char pad_000[0x8];
    unsigned short field_008;               // +0x8
    __declspec(noinline) int LoadMasked(int mask) const;
};

#pragma code_seg(".text$01accessor")
int ObjectAccessor_0040acc0::LoadMasked(int mask) const {
    return (int)field_008 & mask;
}
#pragma code_seg()
