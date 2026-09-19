// 0x00427C90..0x00427CA2 (19 bytes): subtract from the countdown at +0x08 and
// clamp it at zero.
//
// Retail subtracts the incoming halfword from the signed countdown, reloads the
// field, clears it when the result went negative and returns zero.  The object
// arrives in EAX and the value in CX.

struct Countdown_00427c90 {
    unsigned char unknown_00[0x08];
    short value;                           // +0x08

    __declspec(noinline) int Subtract(short amount);
};

#pragma code_seg(".text$01sub")
int Countdown_00427c90::Subtract(short amount) {
    value = value - amount;
    if (value < 0) {
        value = 0;
    }
    return 0;
}
#pragma code_seg()
