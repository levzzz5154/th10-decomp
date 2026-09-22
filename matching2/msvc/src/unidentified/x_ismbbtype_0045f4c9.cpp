extern "C" unsigned char data_00497fa1[];
extern "C" unsigned short* data_004739d8;

extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned char character, unsigned int wide_mask, unsigned char byte_mask) {
    if ((data_00497fa1[character] & byte_mask) == 0) {
        unsigned int result = wide_mask ? data_004739d8[character] & wide_mask : 0;
        if (result == 0) return 0;
    }
    return 1;
}
