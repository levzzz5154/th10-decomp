extern "C" unsigned char data_0046bd3c[20];

// 0x0045C3F1..0x0045C40E: True when the word is absent from a ten-word table.
extern "C" int __cdecl asm_FUN_0045c3f1_0045c3f1(short value) {
    unsigned int offset = 0;
    do {
        if (value == *reinterpret_cast<const short*>(data_0046bd3c + offset))
            return 0;
        offset += 2;
    } while (offset < 20);
    return 1;
}
