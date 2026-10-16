struct Rec12 {
    int words[0x77];
};
__declspec(noinline) Rec12* Copy2(Rec12* destination, const Rec12* source);
#pragma code_seg(".text$01accessor")
Rec12* Copy2(Rec12* destination, const Rec12* source) {
    *destination = *source;
    return destination;
}
#pragma code_seg()
