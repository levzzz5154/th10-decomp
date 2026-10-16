class FrameTimer {
public:
    unsigned char pad_000[4];
    __declspec(noinline) void Advance(float delta);
    __declspec(noinline) void AdvanceFrames(int frames);
};
#pragma code_seg(".text$01accessor")
void FrameTimer::AdvanceFrames(int frames) {
    Advance((float)frames);
}
#pragma code_seg()
