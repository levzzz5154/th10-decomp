extern "C" unsigned char g_mbc_char_table[];
extern "C" unsigned short* g_crt_ctype_table;

extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned char character, unsigned int wide_mask, unsigned char byte_mask) {
    if ((g_mbc_char_table[character] & byte_mask) == 0) {
        unsigned int result = wide_mask ? g_crt_ctype_table[character] & wide_mask : 0;
        if (result == 0) return 0;
    }
    return 1;
}
