struct Rec_0041c0a0 {
    int words[0x77];
};
__declspec(noinline) Rec_0041c0a0* Copy_0041c0a0(Rec_0041c0a0* destination, const Rec_0041c0a0* source);
#pragma code_seg(".text$01accessor")
Rec_0041c0a0* Copy_0041c0a0(Rec_0041c0a0* destination, const Rec_0041c0a0* source) {
    *destination = *source;
    return destination;
}
#pragma code_seg()
