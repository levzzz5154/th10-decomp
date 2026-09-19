// 0x0043E580..0x0043E59F: clear the record that arrives in EDX and fill the
// 0x200-byte table at +0x408 with 0xFF.
void* __fastcall ResetState_0043e580(int unused, void* record) {
    unsigned int* words = (unsigned int*)record;
    for (unsigned int index = 0; index < 0x14b4; ++index) {
        words[index] = 0;
    }
    unsigned int* table = (unsigned int*)((unsigned char*)record + 0x408);
    for (unsigned int index = 0; index < 0x80; ++index) {
        table[index] = 0xffffffff;
    }
    return record;
}
