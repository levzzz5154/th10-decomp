// 0x00427CC0..0x00427CD5 (22 bytes): the countdown at +0x08 in seconds.
//
// Retail sign-extends the 16-bit field and divides by 20 with the magic
// 0x66666667 and a shift of 3, so the source is a signed short divided by 20.
// The object arrives in EAX.

struct Countdown3 {
    unsigned char unknown_00[0x08];
    short value;                   // +0x08

    __declspec(noinline) int Seconds();
};

#pragma code_seg(".text$01sec")
int Countdown3::Seconds() {
    return value / 20;
}
#pragma code_seg()
