struct EmbeddedTimer_004050d0 {
    unsigned char unknown_0000[0x30];
    int current;
    int previous;
    float subframe;
    float* default_rate;
    unsigned int flags;
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void EmbeddedTimer_004050d0::Reset() {
    if ((flags & 1) == 0) {
        previous = 0;
        current = -999999;
        subframe = 0.0f;
        default_rate = (float*)0x00476f78;
        flags |= 1;
    }
    previous = 0;
    subframe = 0.0f;
    current = -1;
}
#pragma code_seg()
