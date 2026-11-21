extern "C" unsigned char g_crt_ctype_range_table[20];

// 0x0045C3F1..0x0045C40E: True when the word is absent from a ten-word table.
extern "C" int __cdecl crt_libc_getqloc_TestDefaultCountry(short value) {
    unsigned int offset = 0;
    do {
        if (value == *reinterpret_cast<const short*>(g_crt_ctype_range_table + offset))
            return 0;
        offset += 2;
    } while (offset < 20);
    return 1;
}
