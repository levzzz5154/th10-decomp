struct CrtWordPair { unsigned int key; unsigned int value; };
extern "C" CrtWordPair data_00473c98[29];

// 0x0045E894..0x0045E8B3: Look up a CRT key in the 29-entry table.
extern "C" unsigned int __cdecl asm_unassigned_0045e894(unsigned int key) {
    for (int index = 0; index < 29; ++index) {
        if (data_00473c98[index].key == key)
            return data_00473c98[index].value;
    }
    return 0;
}
