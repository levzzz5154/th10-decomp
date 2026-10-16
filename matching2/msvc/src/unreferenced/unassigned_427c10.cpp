// 0x00427C10: scale a float pair by 100 and truncate it to an integer pair.
// Native LTCG gives it the source in ESI and the destination in EDI.
struct FloatPair {
    float x;
    float y;
};

struct IntPair {
    int x;
    int y;
};

__declspec(noinline) void ScaleToHundredths(IntPair* out,
                                                     const FloatPair* in);

#pragma code_seg(".text$01scale")
void ScaleToHundredths(IntPair* out, const FloatPair* in) {
    out->x = (int)(in->x * 100.0f);
    out->y = (int)(in->y * 100.0f);
}
#pragma code_seg()
