// 0x0043E4D0..0x0043E4F8: stamp a duration in frames onto the value record
// reached through +0x5208.  The holder is consumed before the conversion, so
// the value record takes the callee-saved ESI across __ftol2 while the holder
// stays dead in EAX.
struct TimeValue_0043e4d0 {
    unsigned char pad_000[0x14];
    int frames;                      // +0x14
    int copy;                        // +0x18
    int flag;                        // +0x1C
};

struct Holder_0043e4d0 {
    unsigned char pad_000[0x5208];
    TimeValue_0043e4d0* record;      // +0x5208
    unsigned int field_520c;         // +0x520C
    unsigned int field_5210;         // +0x5210
    __declspec(noinline) void SetSeconds(float seconds);
};

#pragma code_seg(".text$01accessor")
void Holder_0043e4d0::SetSeconds(float seconds) {
    TimeValue_0043e4d0* target = record;
    if (target) {
        target->flag = 1;
        int frames = (int)(seconds * 60.0f);
        target->frames = frames;
        target->copy = frames;
    }
}
#pragma code_seg()
