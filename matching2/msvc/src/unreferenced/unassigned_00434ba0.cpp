// 0x00434BA0: store one flag bit (bit 4 of the word at +0x60).
struct FlagWord_00434ba0 {
    unsigned char reserved_000[0x60];
    unsigned int low_bits : 4;       // +0x60 bits 0..3
    unsigned int enabled : 1;        // +0x60 bit 4
    unsigned int high_bits : 27;
    __declspec(noinline) void SetEnabled(unsigned int value);
};

#pragma code_seg(".text$01accessor")
void FlagWord_00434ba0::SetEnabled(unsigned int value) {
    enabled = value;
}
#pragma code_seg()
