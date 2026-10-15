// 0x0043C310..0x0043C3BE: the dim update task (Screen modes 6
// and 7, registered at priority 14). The object is handed to the callback in ECX.
//
// The callback advances the fractional frame position by the frame delta
// published at +0x3C and republishes the animation parameters the drawing pass
// reads back: +0x18 is the value derived from the elapsed frame position, and
// +0x30 keeps the frame the previous tick ended on.
struct ScreenDim {
    unsigned char pad_00[0x18];
    int value;                   // +0x18  value derived from the frame position
    int length;                  // +0x1C  total length, 0 while undetermined
    unsigned char pad_20[0x0C];
    int mode;                    // +0x2C  nonzero for the frame-limited mode
    int previous;                // +0x30  frame published by the previous tick
    int frame;                   // +0x34  current frame
    float elapsed;               // +0x38  fractional frame position
    const float* delta;          // +0x3C  frame delta of the current tick
    int Tick();
};

int ScreenDim::Tick() {
    if (mode == 0) {
        int divisor = length;
        if (divisor != 0 && frame <= divisor)
            value = (int)(elapsed * 128.0f / divisor);
    } else {
        if (frame <= 8)
            value = 128 - (int)(elapsed * 16.0f);
        else
            return 7;
    }
    int current = frame;
    const float* delta = this->delta;
    previous = current;
    if (*delta > 0.99f && *delta < 1.01f) {
        frame = current + 1;
        elapsed = elapsed + 1.0f;
        return 1;
    }
    elapsed = *delta + elapsed;
    frame = (int)elapsed;
    return 1;
}
