// padding: 0x00405856..0x0040585F
// Inter-function INT3 alignment fill, not code.
#pragma data_seg(".d002014")
extern "C" unsigned char text_padding_00405856[] = {
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
};
#pragma data_seg()
